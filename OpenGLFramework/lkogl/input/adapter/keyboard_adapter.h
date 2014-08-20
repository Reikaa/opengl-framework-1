//
//  keyboard_adapter.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__keyboard_adapter__
#define __OpenGLFramework__keyboard_adapter__

#include "../keyboard.h"
#include "../../sdl.h"

namespace lkogl {
    namespace input {
        namespace adapter {
            class KeyboardAdapter {
                Keyboard &keyboard_;
                
            public:
                KeyboardAdapter(Keyboard &k);
                
                bool processEvent(const SDL_Event &e) const;
                
                Keyboard::Key mapKey(const int) const;
            };
        }
    }
}

#endif /* defined(__OpenGLFramework__keyboard_adapter__) */
