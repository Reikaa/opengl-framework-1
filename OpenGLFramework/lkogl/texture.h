//
//  texture.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__texture__
#define __OpenGLFramework__texture__

#include <vector>

#include "image.h"
#include "program.h"

namespace lkogl {
    namespace graphics {
        class TextureException {};
        
        class TextureResource {
            const GLenum textureTarget_ = GL_TEXTURE_2D;
            mutable GLuint handle_;
            const int width_;
            const int height_;

        public:
            
            TextureResource(const TextureResource&) = delete;
            TextureResource(TextureResource&&);
            TextureResource(int width, int height);
            ~TextureResource();
            
            void replaceImage(const utils::Image& image) throw (TextureException);
            
        private:
            explicit TextureResource(int handle, int w, int h);
            GLuint generateTexture() const;
            
            friend class FrameBufferResource;
            friend class TextureBinding;
        };
        
        
        class TextureBinding {
            const TextureResource& r_;
        public:
            TextureBinding(const TextureResource& r, GLenum slot) : r_(r) {
                glActiveTexture(GL_TEXTURE0+slot);
                glBindTexture(r.textureTarget_, r_.handle_);
            }
            
            ~TextureBinding() {
                glBindTexture(r_.textureTarget_, 0);
                glActiveTexture(GL_TEXTURE0);
            }
        };
        
        class Texture {
            const std::shared_ptr<TextureResource> resource_;
        public:
            Texture(const utils::Image&) throw (TextureException);
            Texture(const Texture&);
            ~Texture();
        private:            
            friend class TextureUse;
            friend class TextureRendering;
        };
        
        class TextureUse {
            TextureBinding b_;
        public:
            TextureUse(const ProgramUse& p, const Texture&);
            TextureUse(const ProgramUse& p, const Texture&, int slto);
            TextureUse(GLuint loc, const Texture&, int slto);
            ~TextureUse();
        };
    }
}

#endif /* defined(__OpenGLFramework__texture__) */
