//
//  keyboard.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__keyboard__
#define __OpenGLFramework__keyboard__

#include <set>
#include <stdio.h>

namespace lkogl {
    namespace input {
        namespace adapter {
            class KeyboardAdapter;
        }
        
        class Keyboard {
        public:
            enum class Key {
                BACKSPACE,
                TAB,
                ENTER,
                PAUSE,
                CAPS_LOCK,
                ESCAPE,
                SPACE,
                PAGE_UP,
                PAGE_DOWN,
                END,
                HOME,
                LEFT_ARROW,
                UP_ARROW,
                RIGHT_ARROW,
                DOWN_ARROW,
                INSERT,
                DELETE,
                NUMBER_0,
                NUMBER_1,
                NUMBER_2,
                NUMBER_3,
                NUMBER_4,
                NUMBER_5,
                NUMBER_6,
                NUMBER_7,
                NUMBER_8,
                NUMBER_9,
                LETTER_A,
                LETTER_B,
                LETTER_C,
                LETTER_D,
                LETTER_E,
                LETTER_F,
                LETTER_G,
                LETTER_H,
                LETTER_I,
                LETTER_J,
                LETTER_K,
                LETTER_L,
                LETTER_M,
                LETTER_N,
                LETTER_O,
                LETTER_P,
                LETTER_Q,
                LETTER_R,
                LETTER_S,
                LETTER_T,
                LETTER_U,
                LETTER_V,
                LETTER_W,
                LETTER_X,
                LETTER_Y,
                LETTER_Z,
                SELECT_KEY,
                NUMPAD_0,
                NUMPAD_1,
                NUMPAD_2,
                NUMPAD_3,
                NUMPAD_4,
                NUMPAD_5,
                NUMPAD_6,
                NUMPAD_7,
                NUMPAD_8,
                NUMPAD_9,
                MULTIPLY,
                ADD,
                SUBTRACT,
                DECIMAL_POINT,
                DIVIDE,
                F_1,
                F_2,
                F_3,
                F_4,
                F_5,
                F_6,
                F_7,
                F_8,
                F_9,
                F_10,
                F_11,
                F_12,
                NUM_LOCK,
                SCROLL_LOCK,
                SEMICOLON,
                EQUAL_SIGN,
                COMMA,
                DASH,
                PERIOD,
                FORWARD_SLASH,
                GRAVE_ACCENT,
                OPEN_BRACKET,
                BACK_SLASH,
                CLOSE_BRAKET,
                SINGLE_QUOTE,
                
                UNKNOWN
            };
            
        private:
            std::set<Key> keySet_;
            std::set<Key> prevKeySet_;
        public:
            Keyboard();
            bool isDown(Key k) const;
            bool isUp(Key k) const;
            bool pressed(Key k) const;
            bool released(Key k) const;
            void update();
        private:
            void setKeyDown(Key k);
            void setKeyUp(Key k);
            
            friend class adapter::KeyboardAdapter;
        };
    }
}

#endif /* defined(__OpenGLFramework__keyboard__) */
