//
//  keyboard_adapter.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./keyboard_adapter.h"

namespace lkogl {
    namespace input {
        namespace adapter {
        
            KeyboardAdapter::KeyboardAdapter(Keyboard &k) : keyboard_(k)
            {
            }
            
            bool KeyboardAdapter::processEvent(const SDL_Event &e) const
            {
                switch( e.type ){
                    case SDL_KEYDOWN:
                        keyboard_.setKeyDown(mapKey(e.key.keysym.sym));
                        return true;
                        
                    case SDL_KEYUP:
                        keyboard_.setKeyUp(mapKey(e.key.keysym.sym));
                        return true;
                }
                
                return false;
            }
            
            Keyboard::Key KeyboardAdapter::mapKey(const int keycode) const {
                switch(keycode) {
                    case SDLK_BACKSPACE: return Keyboard::Key::BACKSPACE;
                    case SDLK_TAB: return Keyboard::Key::TAB;
                    case SDLK_RETURN: return Keyboard::Key::ENTER;
                    case SDLK_PAUSE: return Keyboard::Key::PAUSE;
                    case SDLK_CAPSLOCK: return Keyboard::Key::CAPS_LOCK;
                    case SDLK_ESCAPE: return Keyboard::Key::ESCAPE;
                    case SDLK_SPACE: return Keyboard::Key::SPACE;
                    case SDLK_PAGEUP: return Keyboard::Key::PAGE_UP;
                    case SDLK_PAGEDOWN: return Keyboard::Key::PAGE_DOWN;
                    case SDLK_END: return Keyboard::Key::END;
                    case SDLK_HOME: return Keyboard::Key::HOME;
                    case SDLK_LEFT: return Keyboard::Key::LEFT_ARROW;
                    case SDLK_UP: return Keyboard::Key::UP_ARROW;
                    case SDLK_RIGHT: return Keyboard::Key::RIGHT_ARROW;
                    case SDLK_DOWN: return Keyboard::Key::DOWN_ARROW;
                    case SDLK_INSERT: return Keyboard::Key::INSERT;
                    case SDLK_DELETE: return Keyboard::Key::DELETE;
                    case SDLK_0: return Keyboard::Key::NUMBER_0;
                    case SDLK_1: return Keyboard::Key::NUMBER_1;
                    case SDLK_2: return Keyboard::Key::NUMBER_2;
                    case SDLK_3: return Keyboard::Key::NUMBER_3;
                    case SDLK_4: return Keyboard::Key::NUMBER_4;
                    case SDLK_5: return Keyboard::Key::NUMBER_5;
                    case SDLK_6: return Keyboard::Key::NUMBER_6;
                    case SDLK_7: return Keyboard::Key::NUMBER_7;
                    case SDLK_8: return Keyboard::Key::NUMBER_8;
                    case SDLK_9: return Keyboard::Key::NUMBER_9;
                    case SDLK_a: return Keyboard::Key::LETTER_A;
                    case SDLK_b: return Keyboard::Key::LETTER_B;
                    case SDLK_c: return Keyboard::Key::LETTER_C;
                    case SDLK_d: return Keyboard::Key::LETTER_D;
                    case SDLK_e: return Keyboard::Key::LETTER_E;
                    case SDLK_f: return Keyboard::Key::LETTER_F;
                    case SDLK_g: return Keyboard::Key::LETTER_G;
                    case SDLK_h: return Keyboard::Key::LETTER_H;
                    case SDLK_i: return Keyboard::Key::LETTER_I;
                    case SDLK_j: return Keyboard::Key::LETTER_J;
                    case SDLK_k: return Keyboard::Key::LETTER_K;
                    case SDLK_l: return Keyboard::Key::LETTER_L;
                    case SDLK_m: return Keyboard::Key::LETTER_M;
                    case SDLK_n: return Keyboard::Key::LETTER_N;
                    case SDLK_o: return Keyboard::Key::LETTER_O;
                    case SDLK_p: return Keyboard::Key::LETTER_P;
                    case SDLK_q: return Keyboard::Key::LETTER_Q;
                    case SDLK_r: return Keyboard::Key::LETTER_R;
                    case SDLK_s: return Keyboard::Key::LETTER_S;
                    case SDLK_t: return Keyboard::Key::LETTER_T;
                    case SDLK_u: return Keyboard::Key::LETTER_U;
                    case SDLK_v: return Keyboard::Key::LETTER_V;
                    case SDLK_w: return Keyboard::Key::LETTER_W;
                    case SDLK_x: return Keyboard::Key::LETTER_X;
                    case SDLK_y: return Keyboard::Key::LETTER_Y;
                    case SDLK_z: return Keyboard::Key::LETTER_Z;
                    case SDLK_SELECT: return Keyboard::Key::SELECT_KEY;
                    case SDLK_KP_0: return Keyboard::Key::NUMPAD_0;
                    case SDLK_KP_1: return Keyboard::Key::NUMPAD_1;
                    case SDLK_KP_2: return Keyboard::Key::NUMPAD_2;
                    case SDLK_KP_3: return Keyboard::Key::NUMPAD_3;
                    case SDLK_KP_4: return Keyboard::Key::NUMPAD_4;
                    case SDLK_KP_5: return Keyboard::Key::NUMPAD_5;
                    case SDLK_KP_6: return Keyboard::Key::NUMPAD_6;
                    case SDLK_KP_7: return Keyboard::Key::NUMPAD_7;
                    case SDLK_KP_8: return Keyboard::Key::NUMPAD_8;
                    case SDLK_KP_9: return Keyboard::Key::NUMPAD_9;
                    case SDLK_KP_MULTIPLY: return Keyboard::Key::MULTIPLY;
                    case SDLK_KP_PLUS: return Keyboard::Key::ADD;
                    case SDLK_KP_MINUS: return Keyboard::Key::SUBTRACT;
                    case SDLK_KP_DECIMAL: return Keyboard::Key::DECIMAL_POINT;
                    case SDLK_KP_DIVIDE: return Keyboard::Key::DIVIDE;
                    case SDLK_F1: return Keyboard::Key::F_1;
                    case SDLK_F2: return Keyboard::Key::F_2;
                    case SDLK_F3: return Keyboard::Key::F_3;
                    case SDLK_F4: return Keyboard::Key::F_4;
                    case SDLK_F5: return Keyboard::Key::F_5;
                    case SDLK_F6: return Keyboard::Key::F_6;
                    case SDLK_F7: return Keyboard::Key::F_7;
                    case SDLK_F8: return Keyboard::Key::F_8;
                    case SDLK_F9: return Keyboard::Key::F_9;
                    case SDLK_F10: return Keyboard::Key::F_10;
                    case SDLK_F11: return Keyboard::Key::F_11;
                    case SDLK_F12: return Keyboard::Key::F_12;
                    case SDLK_NUMLOCKCLEAR: return Keyboard::Key::NUM_LOCK;
                    case SDLK_SCROLLLOCK: return Keyboard::Key::SCROLL_LOCK;
                    case SDLK_SEMICOLON: return Keyboard::Key::SEMICOLON;
                    case SDLK_EQUALS: return Keyboard::Key::EQUAL_SIGN;
                    case SDLK_COMMA: return Keyboard::Key::COMMA;
                    case SDLK_MINUS: return Keyboard::Key::DASH;
                    case SDLK_PERIOD: return Keyboard::Key::PERIOD;
                    case SDLK_SLASH: return Keyboard::Key::FORWARD_SLASH;
                    case SDLK_BACKQUOTE: return Keyboard::Key::GRAVE_ACCENT;
                    case SDLK_LEFTBRACKET: return Keyboard::Key::OPEN_BRACKET;
                    case SDLK_BACKSLASH: return Keyboard::Key::BACK_SLASH;
                    case SDLK_RIGHTBRACKET: return Keyboard::Key::CLOSE_BRAKET;
                    case SDLK_QUOTE: return Keyboard::Key::SINGLE_QUOTE;
                }
                return Keyboard::Key::UNKNOWN;
            };
            
        }
    }
}