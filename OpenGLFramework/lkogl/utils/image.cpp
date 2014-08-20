//
//  image.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./image.h"
#include "./file_path.h"

namespace lkogl {
    namespace utils {
        Image::Image(const std::string& name) throw (Exception)
        : surface_(load(Path().relative(name)))
        {
        
        }
        
        SDL_Surface* Image::load(const std::string& path) throw (Exception)
        {
            SDL_Surface *image = IMG_Load(path.c_str());
            if(!image) {
                throw Exception("Image not found");
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