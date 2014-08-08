//
//  texture.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__texture__
#define __OpenGLFramework__texture__

#include <stdio.h>

#include "opengl.h"
#include "image.h"

namespace lkogl {
    namespace graphics {
        class TextureException {};
        
        class Texture {
            GLuint handle_;
        public:
            Texture(const utils::Image&) throw (TextureException);
            Texture(const Texture&&);
            ~Texture();
            
            const GLuint& handle() { return handle_; }
        private:
            GLuint convert(const utils::Image& img) throw (TextureException);
        };
    }
}

#endif /* defined(__OpenGLFramework__texture__) */
