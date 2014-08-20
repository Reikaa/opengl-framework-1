//
//  hover_behaviour.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 16.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__hover_behaviour__
#define __OpenGLFramework__hover_behaviour__

#include <functional>
#include "behaviour.h"

namespace lkogl {
    namespace ui {
        namespace behaviour {
            class ClickableBehaviour : public Behaviour {
                const std::function< void(void) > callback_;
            public:
                ClickableBehaviour(const std::function< void(void) >& callback = [](void){});
                ~ClickableBehaviour();
                
                virtual void onInit(Element& el);
                virtual bool onFocus(Element& el);
                virtual bool onBlur(Element& el);
                virtual bool onContactBegin(Element& el, const math::Vec2<int>& pos);
                virtual bool onContactEnd(Element& el, const math::Vec2<int>& pos);
                virtual bool onContactMove(Element& el, const math::Vec2<int>& pos);
                virtual bool onContactCancel(Element& el);
            };
        }
    }
}

#endif /* defined(__OpenGLFramework__hover_behaviour__) */
