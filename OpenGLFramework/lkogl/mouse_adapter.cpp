//
//  mouse_adapter.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "mouse_adapter.h"

namespace lkogl {
    namespace input {
        namespace adapter {
            
            MouseAdapter::MouseAdapter(Mouse &m) : mouse_(m)
            {
            }
            
            bool MouseAdapter::processEvent(const SDL_Event &e) const
            {
                switch( e.type ){
                    case SDL_MOUSEBUTTONDOWN:
                        mouse_.setDown(mapButton(e.button.which));
                        return true;
                    case SDL_MOUSEBUTTONUP:
                        mouse_.setUp(mapButton(e.button.which));
                        return true;
                    case SDL_MOUSEWHEEL:
                        mouse_.scroll(e.wheel.x, e.wheel.y);
                        return true;
                    case SDL_MOUSEMOTION:
                        mouse_.move(e.motion.xrel, e.motion.yrel);
                        return true;
                }
                
                return false;
            }
            
            Mouse::Button MouseAdapter::mapButton(const int i) const
            {
                switch(i) {
                    case 1: return Mouse::Button::LEFT;
                    case 2: return Mouse::Button::RIGHT;
                    case 3: return Mouse::Button::MIDDLE;
                    default: return Mouse::Button::UNKNOWN;
                }
            };
            
        }
    }
}