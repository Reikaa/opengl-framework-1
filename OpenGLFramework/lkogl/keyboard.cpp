//
//  keyboard.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "keyboard.h"

namespace lkogl {
    namespace input {
        Keyboard::Keyboard() {
        }
        
        bool Keyboard::isDown(Key k) const {
            return keySet_.find(k) != keySet_.end();
        }
        
        bool Keyboard::isUp(Key k) const {
            return keySet_.find(k) == keySet_.end();
        }
        
        bool Keyboard::pressed(Key k) const {
            return prevKeySet_.find(k) == prevKeySet_.end() && isDown(k);
        }
        
        bool Keyboard::released(Key k) const {
            return prevKeySet_.find(k) != prevKeySet_.end() && isUp(k);
        }
        
        void Keyboard::update() {
            prevKeySet_.clear();
            prevKeySet_.insert(keySet_.begin(), keySet_.end());
        }
        
        void Keyboard::setKeyUp(Key k) {
            keySet_.erase(k);
        }
        
        void Keyboard::setKeyDown(Key k) {
            keySet_.insert(k);
        }
    }
}