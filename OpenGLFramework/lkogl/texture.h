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
#include "opengl.h"
#include "image.h"
#include "program.h"

namespace lkogl {
    namespace graphics {
        class TextureException {};
        
        class TextureResource {
            const GLenum textureTarget_ = GL_TEXTURE_2D;
            const std::vector<GLuint> handles_;
            const GLuint numTextures_;
            const int width_;
            const int height_;
            
            const struct Target {
                GLuint frameBuffer;
                GLuint renderBuffer;
            } targets_;
        public:
            class SlotBinding {
                const TextureResource& r_;
            public:
                SlotBinding(const TextureResource& r, GLenum slot, GLuint textureNum) : r_(r) {
                    glActiveTexture(GL_TEXTURE0+slot);
                    glBindTexture(r.textureTarget_, r_.handles_[textureNum]);
                }
                
                ~SlotBinding() {
                    glBindTexture(r_.textureTarget_, 0);
                    glActiveTexture(GL_TEXTURE0);
                }
            };
            
            class RenderTargetBinding {
                const TextureResource& r_;
            public:
                RenderTargetBinding(const TextureResource& r) : r_(r) {
                    glBindTexture(GL_TEXTURE_2D,0);
                    glBindFramebuffer(GL_FRAMEBUFFER, r.targets_.frameBuffer);
                    
                    glViewport(0, 0, r.width_, r.height_);
                }
                
                ~RenderTargetBinding() {
                    glBindTexture(GL_TEXTURE_2D,0);
                    glBindFramebuffer(GL_FRAMEBUFFER, 0);
                }
            };
            
            TextureResource(const TextureResource&) = delete;
            TextureResource(TextureResource&&) = delete;
            TextureResource(int width, int height, std::vector<GLenum> attachments);
            ~TextureResource();
            
            void replaceImage(const utils::Image& image) throw (TextureException);
            void use() const;
            
        private:
            std::vector<GLuint> generateTexture(GLuint num) const;
            Target generateRenderTarget(std::vector<GLenum>) const;
        };
        
        class Texture {
            const std::shared_ptr<TextureResource> resource_;
            const GLuint slot_ = 1;
        public:
            Texture(const utils::Image&, GLuint slot) throw (TextureException);
            Texture(const utils::Image&) throw (TextureException);
            Texture(int width, int height, GLuint slot) throw (TextureException);
            Texture(int width, int height) throw (TextureException);
            explicit Texture(int width, int height, std::vector<GLenum>, GLuint slot) throw (TextureException);
            explicit Texture(const utils::Image&, std::vector<GLenum>, GLuint slot) throw (TextureException);
            Texture(const Texture&);
            ~Texture();
        private:            
            friend class TextureUse;
            friend class TextureRendering;
        };
        
        class TextureUse {
            TextureResource::SlotBinding b_;
        public:
            TextureUse(const Program& p, const Texture&);
            TextureUse(const Program& p, const Texture&, int num);
            ~TextureUse();
        };
        
        class TextureRendering {
            TextureResource::RenderTargetBinding b_;
        public:
            TextureRendering(const Texture&);
            ~TextureRendering();
        };
    }
}

#endif /* defined(__OpenGLFramework__texture__) */
