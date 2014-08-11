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
#include "program.h"

namespace lkogl {
    namespace graphics {
        class TextureException {};
        
        class TextureResource {
            const GLuint handle_;
        public:
            class Binding {
                const TextureResource& r_;
            public:
                Binding(const TextureResource& r, GLenum slot) : r_(r) {
                    glActiveTexture(GL_TEXTURE0+slot);
                    glBindTexture(GL_TEXTURE_2D, r_.handle_);
                }
                
                ~Binding() {
                    glBindTexture(GL_TEXTURE_2D, 0);
                    glActiveTexture(GL_TEXTURE0);
                }
            };
            
            TextureResource(const TextureResource&) = delete;
            TextureResource(TextureResource&&) = delete;
            TextureResource();
            ~TextureResource();
            
            void use() const;
            
        private:
            GLuint generate() const;
        };
        
        class Texture {
            const std::shared_ptr<TextureResource> resource_;
        public:
            Texture(const utils::Image&) throw (TextureException);
            Texture(const Texture&);
            ~Texture();
        private:
            void replaceImage(const utils::Image& img) throw (TextureException);
            
            friend class TextureUse;
        };
        
        class TextureUse {
            TextureResource::Binding b_;
        public:
            TextureUse(const Program& p, const Texture&);
            ~TextureUse();
        };
    }
}

#endif /* defined(__OpenGLFramework__texture__) */
