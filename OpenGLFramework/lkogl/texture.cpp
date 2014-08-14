//
//  texture.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "texture.h"
#include <iostream>

namespace lkogl {
    namespace graphics {
        TextureResource::TextureResource(int width, int height) :
        handle_(generateTexture()), width_(width), height_(height)
        {
        }
        
        TextureResource::TextureResource(TextureResource&& old) :
        handle_(old.handle_), width_(old.width_), height_(old.height_)
        {
            old.handle_ = 0;
        }
        
        TextureResource::TextureResource(int i, int w, int h) :
        handle_(i), width_(w), height_(h)
        {
        }
        
        GLuint TextureResource::generateTexture() const {
            GLuint handle;
            glGenTextures(1, &handle);
            
            if(!handle) {
                throw "Texture could not be created";
            }
           
            return handle;
        }
        
        TextureResource::~TextureResource() {
            if(handle_) {
                glDeleteTextures(1, &handle_);
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
            
            TextureBinding b(*this, 1);
            
            glTexImage2D(textureTarget_, 0, mode, width_, height_, 0, modeInternal, GL_UNSIGNED_BYTE, image.pixels());
            glTexParameteri(textureTarget_, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(textureTarget_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }
        
        Texture::Texture(const utils::Image& img) throw (TextureException) :
        resource_(std::make_shared<TextureResource>(img.width(), img.height())) {
            resource_->replaceImage(img);
        }
    
        Texture::Texture(const Texture& tex) : resource_(tex.resource_) {

        }
        
        Texture::~Texture()
        {
        }
        
        TextureUse::TextureUse(const Program& p, const Texture& tex) :
        TextureUse(p, tex, 0)
        {
        }
        
        TextureUse::TextureUse(const Program& p, const Texture& tex, int slot) :
        b_(*tex.resource_.get(), slot)
        {
            glUniform1i(p.handles().samplerPosition, slot);
        }
        
        TextureUse::TextureUse(GLuint loc, const Texture& tex, int slot) :
        b_(*tex.resource_.get(), slot)
        {
            glUniform1i(loc, slot);
        }
        
        TextureUse::~TextureUse()
        {
        }
    }
}