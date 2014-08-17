//
//  hover_behaviour.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 16.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "hover_behaviour.h"
#include "element.h"

#include <iostream>

namespace lkogl {
    namespace ui {
        namespace behaviour {
            HoverBehaviour::HoverBehaviour()
            {
            }
            
            HoverBehaviour::~HoverBehaviour()
            {
            }
            
            
            void HoverBehaviour::onInit(Element& el)
            {
                
            }
            
            bool HoverBehaviour::onFocus(Element& el)
            {
                el.style().setBackground(el.style().background() + math::Vec4<float>{0,0,0,0.2});
                
                return true;
            }
            
            bool HoverBehaviour::onBlur(Element& el)
            {
                el.style().setBackground(el.style().background() - math::Vec4<float>{0,0,0,0.2});
                
                return true;
            }
            
            bool HoverBehaviour::onContactBegin(Element& el)
            {
                el.style().setBackground(el.style().background() + math::Vec4<float>{0,0,0,0.2});
                                
                return true;
            }
            
            bool HoverBehaviour::onContactEnd(Element& el)
            {
                el.style().setBackground(el.style().background() - math::Vec4<float>{0,0,0,0.2});
                
                std::cout << "clicked!" << std::endl;
                
                
                return true;
            }
            
            bool HoverBehaviour::onContactMove(Element& el)
            {
                return true;
            }
            
            
            bool HoverBehaviour::onContactCancel(Element& el)
            {
                el.style().setBackground(el.style().background() - math::Vec4<float>{0,0,0,0.2});
                
                return true;
            }
            
        }
    }
}