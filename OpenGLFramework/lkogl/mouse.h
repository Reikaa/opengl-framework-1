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
            struct {
                int x;
                int y;
            } position;
            
            struct {
                int x;
                int y;
            } delta;
            
            struct {
                int x;
                int y;
            } wheel;
            
            Mouse();
            ~Mouse();
            
            bool isDown(Button k) const;
            bool isUp(Button k) const;
            bool pressed(Button k) const;
            bool released(Button k) const;
            
            void update();
        private:
            void move(int x, int y);
            
            void scroll(int x, int y);
            
            void setUp(Button k);
            
            void setDown(Button k);
            
            friend class adapter::MouseAdapter;
        };
        
    }
}

#endif /* defined(__OpenGLFramework__mouse__) */
