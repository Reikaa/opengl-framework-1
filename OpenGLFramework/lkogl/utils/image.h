//
//  image.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__image__
#define __OpenGLFramework__image__

#include <string>

#include "sdl.h"

namespace lkogl {
    namespace utils {
        class Image {
        public:
            class Exception {
            public:
                Exception(const std::string& msg) {}
                Exception() {}
            };
            
            SDL_Surface* surface_;
            Image(const std::string& name) throw (Exception);
            ~Image();
            
            int width() const;
            int height() const;
            int bytesPerPixel() const;
            const void* pixels() const;
        private:
            SDL_Surface* load(const std::string& path) throw (Exception);
        };
    }
}

#endif /* defined(__OpenGLFramework__image__) */
