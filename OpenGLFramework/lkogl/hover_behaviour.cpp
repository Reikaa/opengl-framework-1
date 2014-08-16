//
//  hover_behaviour.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 16.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "hover_behaviour.h"
#include "element.h"

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
                
                el.layout().setSize(40, 40);
            }
            
            bool HoverBehaviour::onFocus(Element& el)
            {
                if(++focus > 0) {
                    el.style().setBackground({0,0,0,0.7});
                }
                el.layout().setSize(50, 50);
                
                return true;
            }
            
            bool HoverBehaviour::onBlur(Element& el)
            {
                if(--focus == 0) {
                    el.style().setBackground({0,0,0,0.3});
                }
                el.layout().setSize(40, 40);
                
                return true;
            }
            
            bool HoverBehaviour::onContactBegin(Element& el)
            {
                if(++focus > 0) {
                    el.style().setBackground({0,0,0,0.7});
                }
                return true;
            }
            
            bool HoverBehaviour::onContactEnd(Element& el)
            {
                if(--focus == 0) {
                    el.style().setBackground({0,0,0,0.3});
                }
                return true;
            }
            
            bool HoverBehaviour::onContactMove(Element& el)
            {
                return true;
            }
            
            
            bool HoverBehaviour::onContactCancel(Element& el)
            {
                if(--focus == 0) {
                    el.style().setBackground({0,0,0,0.3});
                }
                return true;
            }
            
        }
    }
}