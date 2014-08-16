//
//  mouse.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "mouse.h"


namespace lkogl {
    namespace input {
    
        Mouse::Mouse()
        {
            
        }
        Mouse::~Mouse()
        {
        }
        
        bool Mouse::isDown(Mouse::Button k) const {
            return keySet_.find(k) != keySet_.end();
        }
        
        bool Mouse::isUp(Mouse::Button k) const {
            return keySet_.find(k) == keySet_.end();
        }
        
        bool Mouse::pressed(Mouse::Button k) const {
            return prevKeySet_.find(k) == prevKeySet_.end() && isDown(k);
        }
        
        bool Mouse::released(Mouse::Button k) const {
            return prevKeySet_.find(k) != prevKeySet_.end() && isUp(k);
        }
        
        void Mouse::update()
        {            
            delta.x = delta.y = 0;
            prevKeySet_.clear();
            prevKeySet_.insert(keySet_.begin(), keySet_.end());
        }
        
        void Mouse::move(int x, int y)
        {
            delta.x += x;
            delta.y += y;
        }
        
        void Mouse::setPosition(int x, int y)
        {
            position.x = x;
            position.y = y;
        }
        
        void Mouse::scroll(int x, int y)
        {
            wheel.x += x;
            wheel.y += y;
        }
        
        void Mouse::setUp(Button k) {
            keySet_.erase(k);
        }
        
        void Mouse::setDown(Button k) {
            keySet_.insert(k);
        }
        
    }
}