//
//  hover_behaviour.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 16.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__hover_behaviour__
#define __OpenGLFramework__hover_behaviour__

#include "behaviour.h"

namespace lkogl {
    namespace ui {
        namespace behaviour {
            class HoverBehaviour : public Behaviour {
                char focus = 0;
            public:
                HoverBehaviour();
                ~HoverBehaviour();
                
                virtual void onInit(Element& el);
                virtual bool onFocus(Element& el);
                virtual bool onBlur(Element& el);
                virtual bool onContactBegin(Element& el);
                virtual bool onContactEnd(Element& el);
                virtual bool onContactMove(Element& el);
                virtual bool onContactCancel(Element& el);
            };
        }
    }
}

#endif /* defined(__OpenGLFramework__hover_behaviour__) */
