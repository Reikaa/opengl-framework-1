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
        Texture::Texture(const utils::Image& img) throw (TextureException) : handle_(convert(img)) {
            
        }
        
        Texture::Texture(const Texture&& tex) : handle_(tex.handle_) {
            tex.handle_ = 0;
        }
        
        GLuint Texture::convert(const utils::Image& image) throw (TextureException) {
            GLuint handle;
            int mode;
            int modeInternal;
            
            glGenTextures(1, &handle);
            if(!handle) {
                throw "Texture could not be created";
            }
            
            if(image.bytesPerPixel() == 4) {
                mode = GL_RGBA;
                modeInternal = GL_BGRA;
            } else if(image.bytesPerPixel() == 3) {
                mode = GL_RGB;
                modeInternal = GL_BGR;
            } else {
                throw "Invalid texture format";
            }
            
            glTexImage2D(GL_TEXTURE_2D, 0, mode, image.width(), image.height(), 0, modeInternal, GL_UNSIGNED_BYTE, image.pixels());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glBindTexture(GL_TEXTURE_2D, 0);
            
            return handle;
        }
        
        Texture::~Texture() {
            if(handle_) {
                glDeleteTextures(1, &handle_);
            }
        }
        
        TextureUse::TextureUse(const Program& p, const Texture& tex)
        {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, tex.handle_);
            glUniform1i(p.handles().samplerPosition, 0);
        }
        
        TextureUse::~TextureUse()
        {
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}