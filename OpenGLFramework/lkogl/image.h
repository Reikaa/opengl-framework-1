//
//  image.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__image__
#define __OpenGLFramework__image__

#include <stdio.h>
#include <string>

namespace lkogl {
    namespace utils {
        class ImageException {};
        
        class Image {
        public:
            const int width;
            const int height;
            const int bytesPerPixel;
            const void* pixels;
            Image(const std::string name) throw (ImageException);
            ~Image();
        };
    }
}

#endif /* defined(__OpenGLFramework__image__) */
