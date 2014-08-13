//
//  texture.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "texture.h"

namespace lkogl {
    namespace graphics {
        TextureResource::TextureResource(int width, int height, std::vector<GLenum> attachments) :
            handles_(generateTexture((GLuint)attachments.size())), targets_(generateRenderTarget(attachments)), width_(width), height_(height), numTextures_((GLuint)attachments.size())
        {
        }
        
        std::vector<GLuint> TextureResource::generateTexture(GLuint num) const {
            GLuint handleArray[num];
            glGenTextures(num, handleArray);
            
            if(!*handleArray) {
                throw "Texture could not be created";
            }
            
            return std::vector<GLuint>(handleArray, handleArray+num);
        }
        
        TextureResource::Target TextureResource::generateRenderTarget(std::vector<GLenum> attachments) const
        {
            constexpr uint MAX_BOUND = 32; //32 is the max number of bound textures in OpenGL
            Target t {0,0};
            GLuint numAttachments = (GLuint)attachments.size();
            bool hasDepth = false;
            
            if(attachments.empty()) {
                return t;
            }
            
            if(attachments.size() > MAX_BOUND) {
                throw "too many attachments";
            }
            
            GLenum drawBuffers[MAX_BOUND];
            
            for(int i = 0; i < numAttachments; i++)
            {
                if(attachments[i] == GL_DEPTH_ATTACHMENT)
                {
                    drawBuffers[i] = GL_NONE;
                    hasDepth = true;
                }
                else
                    drawBuffers[i] = attachments[i];
                
                if(attachments[i] == GL_NONE)
                    continue;
                
                if(t.frameBuffer == 0)
                {
                    glGenFramebuffers(1, &t.frameBuffer);
                    glBindFramebuffer(GL_FRAMEBUFFER, t.frameBuffer);
                }
                
                glFramebufferTexture2D(GL_FRAMEBUFFER, attachments[i], textureTarget_, handles_[i], 0);
            }
            
            if(t.frameBuffer == 0) {
                return t;
            }
            
            if(!hasDepth)
            {
                glGenRenderbuffers(1, &t.renderBuffer);
                glBindRenderbuffer(GL_RENDERBUFFER, t.renderBuffer);
                glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width_, height_);
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, t.renderBuffer);
            }
            
            glDrawBuffers(numAttachments, drawBuffers);
            
            if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            {
                throw "Framebuffer creation failed!";
            }
            
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            
            return t;
        }
        
        TextureResource::~TextureResource() {
            glDeleteTextures(numTextures_, &handles_.front());
            if(targets_.frameBuffer) {
                glDeleteFramebuffers(1, &targets_.frameBuffer);
            }
            if(targets_.frameBuffer) {
                glDeleteRenderbuffers(1, &targets_.renderBuffer);
            }
        }
        
        
        
        void TextureResource::replaceImage(const utils::Image& image) throw (TextureException) {
            int mode;
            int modeInternal;
            
            if(image.bytesPerPixel() == 4) {
                mode = GL_RGBA;
                modeInternal = GL_BGRA;
            } else if(image.bytesPerPixel() == 3) {
                mode = GL_RGB;
                modeInternal = GL_BGR;
            } else {
                throw "Invalid texture format";
            }
            
            TextureResource::SlotBinding b(*this, 1, 0);
            
            glTexImage2D(textureTarget_, 0, mode, width_, height_, 0, modeInternal, GL_UNSIGNED_BYTE, image.pixels());
            glTexParameteri(textureTarget_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(textureTarget_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        
        Texture::Texture(const utils::Image& img) throw (TextureException) :
        Texture(img, 1) {
            resource_->replaceImage(img);
        }
        
        Texture::Texture(const utils::Image& img, GLuint slot) throw (TextureException) :
        Texture(img.width(), img.height(), slot) {
            resource_->replaceImage(img);
        }
        
        Texture::Texture(int width, int height, GLuint slot) throw(lkogl::graphics::TextureException) :
            resource_(std::make_shared<TextureResource>(width, height, std::vector<GLenum>{GL_COLOR_ATTACHMENT0})),
            slot_(slot)
        {
            
        }
        
        Texture::Texture(int width, int height) throw(lkogl::graphics::TextureException) :
            Texture(width, height, 1)
        {
            
        }
        
        Texture::Texture(const Texture& tex) : resource_(tex.resource_), slot_(tex.slot_) {

        }
        
        Texture::~Texture()
        {
        }
        
        TextureUse::TextureUse(const Program& p, const Texture& tex) :
        b_(*tex.resource_.get(), tex.slot_, 0)
        {
            glUniform1i(p.handles().samplerPosition, tex.slot_);
        }
        
        TextureUse::~TextureUse()
        {
        }
        
        TextureRendering::TextureRendering(const Texture& tex) :
        b_(*tex.resource_.get())
        {
            
        }
        
        TextureRendering::~TextureRendering()
        {
        }
    }
}