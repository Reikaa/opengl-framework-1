//
//  file_path.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 17.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__file_path__
#define __OpenGLFramework__file_path__

#include "sdl.h"
#include <string>

namespace lkogl {
    namespace utils {
        class Path {
            char* const path_;
            
        public:
            Path();
            ~Path();
            
            const std::string relative(const std::string& p) const;
        };
    }
}

#endif /* defined(__OpenGLFramework__file_path__) */
