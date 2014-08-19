//
//  shader.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include <sstream>
#include <iostream>
#include <queue>

#include "shader.h"

namespace lkogl {
    namespace graphics {
        ShaderException::ShaderException(const std::string& s): msg(s) {}
        ShaderException::~ShaderException() {}
        
        Shader::Shader(ShaderType type, const std::string& source) throw(lkogl::graphics::ShaderException) : handle_(compile(type, source)), uniforms_(extractUniforms(source)) {
            
        }
        
        Shader::Shader(const Shader&& s) throw() : handle_(s.handle_), uniforms_(std::move(s.uniforms_)) {
            s.handle_ = 0;
        }
        
        Shader::~Shader() {
            if(handle_) {
                glDeleteShader(handle_);
            }
        }
        
        GLuint Shader::compile(ShaderType type, const std::string& source) throw (ShaderException) {
            GLuint shaderHandle = glCreateShader(static_cast<int>(type));

            try {
                GLint compileOk;
                GLint errLength;
                GLchar* errMsg;
                const GLchar* csource = source.c_str();
                const GLint lengths[] = {(GLint)source.length()};
                
                glShaderSource(shaderHandle, 1, &csource, lengths);
                glCompileShader(shaderHandle);
                
                glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileOk);
                if(!compileOk) {
                    glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &errLength);
                    errMsg = new GLchar[errLength];
                    glGetShaderInfoLog(shaderHandle, errLength, &errLength, errMsg);
                    
                    throw ShaderException(errMsg);
                }
                
                return shaderHandle;
            } catch(...) {
                glDeleteShader(shaderHandle);
                throw;
            }
        }
        
        
        std::set<Uniform> Shader::extractUniforms(const std::string& source)
        {
            std::set<Uniform> result;

            const std::string UNIFORM_KEYWORD = "uniform";
            const std::string whitespaces (" \t\f\v\n\r;");
            
            size_t startPos = 0;
            size_t findPos = 0;
            
            std::multimap<std::string, Shader::VariableDefinition> structs = extractStructs(source);
            std::queue<VariableDefinition> vars;
            
            while ((findPos = source.find(UNIFORM_KEYWORD, startPos)) != std::string::npos) {
                size_t typeStart = source.find_first_not_of(whitespaces, findPos + UNIFORM_KEYWORD.length());
                size_t typeEnd = source.find_first_of(whitespaces, typeStart);
                size_t nameStart = source.find_first_not_of(whitespaces, typeEnd);
                size_t nameEnd = source.find_first_of(whitespaces, nameStart);
                
                VariableDefinition var {
                    source.substr(typeStart, typeEnd-typeStart),
                    source.substr(nameStart, nameEnd-nameStart)
                };
                
                vars.push(var);
                
                startPos = nameEnd;
            }
            
            while(!vars.empty()) {
                VariableDefinition current = vars.front();
                vars.pop();
                
                auto structDefLB = structs.lower_bound(current.type);
                auto structDefUB = structs.upper_bound(current.type);
                
                if(structDefLB!=structDefUB) {
                    for(;structDefLB != structDefUB;structDefLB++) {
                        vars.push(VariableDefinition {
                            structDefLB->second.type,
                            current.name + "." + structDefLB->second.name,
                        });
                    }
                } else {
                    Uniform::Type type;
                    if(current.type=="float") {
                        type=Uniform::Type::FLOAT;
                    } else if(current.type=="vec2") {
                        type=Uniform::Type::VEC2;
                    } else if(current.type=="vec3") {
                        type=Uniform::Type::VEC3;
                    } else if(current.type=="vec4") {
                        type=Uniform::Type::VEC4;
                    } else if(current.type=="mat4") {
                        type=Uniform::Type::MAT4;
                    } else if(current.type=="sampler2D") {
                        type=Uniform::Type::SAMPLER2D;
                    } else {
                        std::cerr << "invalid type: " << current.type<<": " << current.name << std::endl;
                        throw 1;
                    }
                    result.insert(Uniform(current.name, type));
                }
                
                
            }
            
            return result;
        }
        
        std::multimap<std::string, Shader::VariableDefinition> Shader::extractStructs(const std::string& source)
        {
            
            const std::string STRUCT_KEYWORD = "struct";
            const std::string whitespaces (" \t\f\v\n\r;");
            std::multimap<std::string, Shader::VariableDefinition> result_;

            size_t startPos = 0;
            size_t findPos = 0;
            
            while ((findPos = source.find(STRUCT_KEYWORD, startPos)) != std::string::npos) {
                size_t nameStart = source.find_first_not_of(whitespaces, findPos + STRUCT_KEYWORD.length());
                size_t nameEnd = source.find_first_of(whitespaces, nameStart);
                
                size_t bodyStart = source.find_first_of("{", nameEnd)+1;
                size_t bodyEnd = source.find_first_of("}", nameEnd);
                
                std::string structName = source.substr(nameStart, nameEnd-nameStart);
                
                size_t bodyFindPos = bodyStart;
                
                while(bodyFindPos < bodyEnd) {
                    size_t typeStart = source.find_first_not_of(whitespaces, bodyFindPos);
                    size_t typeEnd = source.find_first_of(whitespaces, typeStart);
                    size_t nameStart = source.find_first_not_of(whitespaces, typeEnd);
                    size_t nameEnd = source.find_first_of(whitespaces, nameStart);
                    
                    if(nameEnd<bodyEnd) {
                        result_.insert(std::make_pair(structName, VariableDefinition{
                            source.substr(typeStart, typeEnd-typeStart),
                            source.substr(nameStart, nameEnd-nameStart)
                        }));
                    }
                    
                    bodyFindPos = nameEnd;
                }
                
                startPos = nameEnd;
            }
            
            return result_;
        }
        
    }
}