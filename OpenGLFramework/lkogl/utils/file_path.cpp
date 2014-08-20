//
//  file_path.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 17.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./file_path.h"

namespace lkogl {
    namespace utils {
        Path::Path() : path_(SDL_GetBasePath())
        {
        }
        
        Path::~Path()
        {
            SDL_free(path_);
        }
        
        const std::string Path::relative(const std::string& p) const
        {
            return path_ + p;
        }
    }
}

