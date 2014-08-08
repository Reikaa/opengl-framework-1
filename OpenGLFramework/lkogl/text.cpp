//
//  text.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 08.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include<fstream>

#include "text.h"
#include "sdl.h"

namespace lkogl {
    namespace utils {

        PlainText::PlainText(const std::string name) throw (FileException) : content(read(name)) {
            
        }
        
        const std::string PlainText::read(const std::string name) const {
            std::ifstream file;
            std::string result = "";
            file.open(basePath() + name);
            if (file.is_open()) {
                std::string line;
                while(std::getline(file, line))
                {
                    result.append(line).append("\n");
                }
            } else {
                throw FileException();
            }
            file.close();
            
            return result;
        }

        PlainText::~PlainText() {}
        
        const std::string PlainText::basePath() const {
            return SDL_GetBasePath();
        }

    }
}