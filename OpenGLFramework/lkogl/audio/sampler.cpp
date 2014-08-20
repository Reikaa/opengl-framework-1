//
//  sampler.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 20.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include <iostream>

#include "./sampler.h"
#include "../utils/file_path.h"

namespace lkogl {
    namespace audio {
        Sampler::Sampler(const std::string& name) throw(lkogl::audio::Sampler::Exception) : handle_(load(utils::Path().relative(name)))
        {
        }
        
        Sampler::~Sampler()
        {
            Mix_FreeChunk(handle_);
        }
        
        void Sampler::play() const
        {
            if(Mix_PlayChannel(-1, handle_, 0)==-1) {
                std::cerr << "Audio playing failed." << std::endl;
            }
        }
        
        Mix_Chunk* const Sampler::load(const std::string& name) const throw(lkogl::audio::Sampler::Exception)
        {
            Mix_Chunk *sample;
            sample=Mix_LoadWAV(name.c_str());
            if(!sample) {
                throw Exception("Sound file could not be loaded.");
            }
            
            return sample;
        }
    }
}