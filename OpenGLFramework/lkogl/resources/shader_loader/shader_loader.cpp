//
//  shader_loader.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 26.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include <set>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>

#include "./shader_loader.h"

namespace lkogl {
    namespace resources {
        namespace shader_loader {
            const std::string INCLUDE_KEYWORD = "include";
            const std::string PREPROCESSOR_BEGIN = "#";
            const std::string WHITESPACE = "\n\t ";
            
            ShaderLoader::ShaderLoader()
            {}
            
            ShaderLoader::ShaderLoader(const utils::Path& path) : path_(path)
            {}
            
            ShaderLoader::~ShaderLoader()
            {}
            
            graphics::shader::Shader ShaderLoader::fromFile(graphics::shader::ShaderType type, const std::string& name) const throw (Exception)
            {
                std::set<std::string> duplicates;
                std::stringstream ss;
                std::stack<std::pair<std::string, std::ifstream>> fileStack;
                
                auto path = path_.relative(name);
                duplicates.insert(path);
                fileStack.push(std::make_pair(path, std::ifstream(path)));
                std::string line;
                
                while(!fileStack.empty())
                {
                    if(!fileStack.top().second.good()) {
                        throw Exception("File not found:" + fileStack.top().first);
                    }
                    while (std::getline(fileStack.top().second, line))
                    {
                        size_t startpos = line.find_first_not_of(WHITESPACE);
                        size_t length = INCLUDE_KEYWORD.length()+PREPROCESSOR_BEGIN.length();
                        
                        std::string p;
                        if(std::string::npos != startpos && line.substr(0, 1) == "#")
                            p = line.substr(startpos, length);
                        if(std::string::npos != startpos && line.substr(startpos, length) == PREPROCESSOR_BEGIN+INCLUDE_KEYWORD)
                        {
                            size_t nameStart = line.find_first_of("\"'", startpos+length) + 1;
                            size_t nameEnd = line.find_first_of("\"'", +nameStart);
                            
                            std::string includeName = line.substr(nameStart, nameEnd-nameStart);
                            
                            if(duplicates.find(path_.relative(includeName)) != duplicates.end()) {
                                throw Exception("Cyclic include");
                            }
                            
                            std::string rel = path_.relative(includeName);
                            fileStack.push(std::make_pair(rel, std::ifstream(rel)));
                        }
                        else
                        {
                            ss << line << std::endl;
                        }
                    }
                    duplicates.erase(fileStack.top().first);
                    fileStack.pop();
                }
                                
                return graphics::shader::Shader(type, ss.str());
            }
        }
    }
}
