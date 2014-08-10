//
//  mouse_adapter.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__mouse_adapter__
#define __OpenGLFramework__mouse_adapter__

#include "mouse.h"
#include "sdl.h"

namespace lkogl {
    namespace input {
        namespace adapter {
            class MouseAdapter {
                Mouse &mouse_;
                
            public:
                MouseAdapter(Mouse &m);
                
                bool processEvent(const SDL_Event &e) const;
                
                Mouse::Button mapButton(const int) const;
            };
        }
    }
}

#endif /* defined(__OpenGLFramework__mouse_adapter__) */
