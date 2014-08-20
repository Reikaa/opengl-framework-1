//
//  element.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 15.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__element__
#define __OpenGLFramework__element__

#include <list>

#include "./layout.h"
#include "./style.h"
#include "./behaviour.h"

namespace lkogl {
    namespace ui {
        
        class Element
        {
            mutable std::list<std::shared_ptr<Element>> children_;
            Layout layout_;
            Style style_;
            const std::shared_ptr<Behaviour> behaviour_;
        public:
            bool hover = false;
            
            Element();
            Element(Length w, Length h);
            Element(const std::shared_ptr<Behaviour> b);
            ~Element();
            
            void addChild(std::shared_ptr<Element>);
            void removeChild(std::shared_ptr<Element>);
            const std::list<std::shared_ptr<Element>>& children() const;
            
            Layout& layout();
            const Layout& layout() const;
            
            const Style& style() const;
            Style& style();
            
            bool render() const;
            
            bool onFocus();
            bool onBlur();
            
            bool onContactBegin(const math::Vec2<int>& pos);
            bool onContactEnd(const math::Vec2<int>& pos);
            bool onContactMove(const math::Vec2<int>& pos);
            bool onContactCancel();
        };
    }
}

#endif /* defined(__OpenGLFramework__element__) */
