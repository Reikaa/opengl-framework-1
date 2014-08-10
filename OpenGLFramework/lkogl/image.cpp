//
//  image.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "image.h"

namespace lkogl {
    namespace utils {
        Image::Image(const std::string& name) throw (ImageException)
        : surface_(load(std::string(SDL_GetBasePath())+name))
        {
        
        }
        
        SDL_Surface* Image::load(const std::string& path) throw (ImageException)
        {
            SDL_Surface *image = IMG_Load(path.c_str());
            if(!image) {
                throw ImageException();
            }
            
            return image;
        }
        
        Image::~Image()
        {
            SDL_FreeSurface(surface_);
        }
        
        int Image::width() const
        {
            return surface_->w;
        }
        
        int Image::height() const
        {
            return surface_->h;
        }
        
        int Image::bytesPerPixel() const
        {
            return surface_->format->BytesPerPixel;
        }
        
        const void* Image::pixels() const
        {
            return surface_->pixels;
        }
    }
}