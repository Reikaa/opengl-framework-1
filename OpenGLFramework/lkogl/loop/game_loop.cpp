//
//  game_loop.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include <chrono>

#include "./game_loop.h"

namespace lkogl {
    namespace loop {
        
        long fps(long fps) {
            return 1000000000 / fps;
        }
        
        long hirestime() {
            return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        }
        
        long lowrestime() {
            return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        }
        
    }
}