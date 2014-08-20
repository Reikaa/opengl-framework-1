//
//  text.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 08.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include<fstream>

#include "./text.h"
#include "./file_path.h"

namespace lkogl {
    namespace utils {

        PlainText::PlainText(const std::string name) throw (Exception) : content(read(name)) {
            
        }
        
        const std::string PlainText::read(const std::string name) const {
            std::ifstream file;
            std::string result = "";
            file.open(Path().relative(name));
            if (file.is_open()) {
                std::string line;
                while(std::getline(file, line))
                {
                    result.append(line).append("\n");
                }
            } else {
                throw Exception("File not found");
            }
            file.close();
            
            return result;
        }

        PlainText::~PlainText() {}

    }
}