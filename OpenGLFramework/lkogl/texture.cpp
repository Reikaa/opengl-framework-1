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
        TextureResource::TextureResource() : handle_(generate())
        {
        }
        
        GLuint TextureResource::generate() const {
            GLuint handle;
            glGenTextures(1, &handle);
            
            if(!handle) {
                throw "Texture could not be created";
            }
            
            return handle;
        }
        
        TextureResource::~TextureResource() {
            glDeleteTextures(1, &handle_);
            printf("texture deleted");
        }
        
        Texture::Texture(const utils::Image& img) throw (TextureException) :
        resource_(std::make_shared<TextureResource>()) {
            replaceImage(img);
            printf("new texture");
        }
        
        Texture::Texture(const Texture& tex) : resource_(tex.resource_) {

        }
        
        void Texture::replaceImage(const utils::Image& image) throw (TextureException) {
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
            
            TextureResource::Binding b(*resource_.get(), 0);
            glTexImage2D(GL_TEXTURE_2D, 0, mode, image.width(), image.height(), 0, modeInternal, GL_UNSIGNED_BYTE, image.pixels());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        
        Texture::~Texture()
        {
        }
        
        TextureUse::TextureUse(const Program& p, const Texture& tex) :
        b_(*tex.resource_.get(), 2)
        {
            glUniform1i(p.handles().samplerPosition, 2);
        }
        
        TextureUse::~TextureUse()
        {
            
        }
    }
}