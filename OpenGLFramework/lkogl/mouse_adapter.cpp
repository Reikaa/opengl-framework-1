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
                        mouse_.setDown(mapButton(e.button.button));
                        return true;
                    case SDL_MOUSEBUTTONUP:
                        mouse_.setUp(mapButton(e.button.button));
                        return true;
                    case SDL_MOUSEWHEEL:
                        mouse_.scroll(e.wheel.x, e.wheel.y);
                        return true;
                    case SDL_MOUSEMOTION:
                        mouse_.move(e.motion.xrel, e.motion.yrel);
                        mouse_.setPosition(e.motion.x, e.motion.y);
                        return true;
                    case SDL_WINDOWEVENT:
                        if(e.window.event == SDL_WINDOWEVENT_LEAVE) {
                            mouse_.setPosition(-1, -1);
                        }
                }
                
                return false;
            }
            
            Mouse::Button MouseAdapter::mapButton(Uint8 i) const
            {
                switch(i) {
                    case SDL_BUTTON_LEFT: return Mouse::Button::LEFT;
                    case SDL_BUTTON_RIGHT: return Mouse::Button::RIGHT;
                    case SDL_BUTTON_MIDDLE: return Mouse::Button::MIDDLE;
                    default: return Mouse::Button::UNKNOWN;
                }
            };
            
        }
    }
}