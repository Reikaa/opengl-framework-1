//
//  mouse.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__mouse__
#define __OpenGLFramework__mouse__

#include <set>
#include "../math/math.h"

namespace lkogl {
    namespace input {
        namespace adapter {
            class MouseAdapter;
        }
        
        class Mouse {
        public:
            enum class Button {
                LEFT,
                MIDDLE,
                RIGHT,
                
                UNKNOWN
            };
            
            std::set<Button> keySet_;
            std::set<Button> prevKeySet_;
        public:
            math::Vec2<int> position;
            
            math::Vec2<int> delta;
            
            math::Vec2<int> wheel;
            
            Mouse();
            ~Mouse();
            
            bool isDown(Button k) const;
            bool isUp(Button k) const;
            bool pressed(Button k) const;
            bool released(Button k) const;
                        
            void update();
        private:
            void move(int x, int y);
            
            void setPosition(int x, int y);
            
            void scroll(int x, int y);
            
            void setUp(Button k);
            
            void setDown(Button k);
            
            friend class adapter::MouseAdapter;
        };
        
    }
}

#endif /* defined(__OpenGLFramework__mouse__) */
