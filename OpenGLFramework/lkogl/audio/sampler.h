//
//  sampler.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 20.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__sampler__
#define __OpenGLFramework__sampler__

#include <string>
#include "../sdl.h"

namespace lkogl {
    namespace audio {
        class Sampler {
            Mix_Chunk* const handle_;
        public:
            class Exception {
            public:
                Exception(const std::string& msg) {}
                ~Exception() {}
            };
            
            Sampler(const std::string& name) throw(Exception);
            ~Sampler();
            
            void play() const;
        private:
            Mix_Chunk* const load(const std::string& name) const throw(Exception);
        };
    }
}

#endif /* defined(__OpenGLFramework__sampler__) */
