//
//  texture.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__texture__
#define __OpenGLFramework__texture__

#include "opengl.h"
#include "image.h"
#include "shader.h"

namespace lkogl {
    namespace graphics {
        class TextureException {};
        
        class Texture {
            mutable GLuint handle_;
        public:
            Texture(const utils::Image&) throw (TextureException);
            Texture(const Texture&&);
            ~Texture();
        private:
            GLuint convert(const utils::Image& img) throw (TextureException);
            
            friend class TextureUse;
        };
        
        class TextureUse {
        public:
            TextureUse(const Program& p, const Texture&);
            ~TextureUse();
        };
    }
}

#endif /* defined(__OpenGLFramework__texture__) */
