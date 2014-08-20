//
//  hover_behaviour.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 16.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "clickable_behaviour.h"
#include "element.h"

#include <iostream>

namespace lkogl {
    namespace ui {
        namespace behaviour {
            ClickableBehaviour::ClickableBehaviour(const std::function< void(void) >& cb) : callback_(cb)
            {
            }
            
            ClickableBehaviour::~ClickableBehaviour()
            {
            }
            
            
            void ClickableBehaviour::onInit(Element& el)
            {
                
            }
            
            bool ClickableBehaviour::onFocus(Element& el)
            {
                el.style().setBackground(el.style().background() + math::Vec4<float>{0,0,0,0.2});
                
                return true;
            }
            
            bool ClickableBehaviour::onBlur(Element& el)
            {
                el.style().setBackground(el.style().background() - math::Vec4<float>{0,0,0,0.2});
                
                return true;
            }
            
            bool ClickableBehaviour::onContactBegin(Element& el, const math::Vec2<int>& pos)
            {
                el.style().setBackground(el.style().background() + math::Vec4<float>{0,0,0,0.2});
                                
                return true;
            }
            
            bool ClickableBehaviour::onContactEnd(Element& el, const math::Vec2<int>& pos)
            {
                el.style().setBackground(el.style().background() - math::Vec4<float>{0,0,0,0.2});
                
                callback_();
                
                
                return true;
            }
            
            bool ClickableBehaviour::onContactMove(Element& el, const math::Vec2<int>& pos)
            {
                return true;
            }
            
            
            bool ClickableBehaviour::onContactCancel(Element& el)
            {
                el.style().setBackground(el.style().background() - math::Vec4<float>{0,0,0,0.2});
                
                return true;
            }
            
        }
    }
}