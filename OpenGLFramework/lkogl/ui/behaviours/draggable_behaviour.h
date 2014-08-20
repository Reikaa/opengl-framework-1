//
//  draggable_behaviour.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 19.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__draggable_behaviour__
#define __OpenGLFramework__draggable_behaviour__

#include <functional>
#include "../behaviour.h"
#include "../layout.h"

namespace lkogl {
    namespace ui {
        namespace behaviour {
            class DraggableBehaviour : public Behaviour {
                math::Vec2<int> baseOffset_;
                math::Vec2<int> basePos_;
                const Layout& clamp_;
            public:
                DraggableBehaviour(const Layout&);
                ~DraggableBehaviour();
                
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

#endif /* defined(__OpenGLFramework__draggable_behaviour__) */
