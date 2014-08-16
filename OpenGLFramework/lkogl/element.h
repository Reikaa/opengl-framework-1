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

#include "layout.h"

namespace lkogl {
    namespace ui {
        class Element
        {
            mutable std::list<std::shared_ptr<Element>> children_;
            Layout layout_;
        public:
            Element();
            Element(Length w, Length h);
            ~Element();
            
            void addChild(std::shared_ptr<Element>);
            void removeChild(std::shared_ptr<Element>);
            const std::list<std::shared_ptr<Element>>& children() const;
            
            Layout& layout() { return layout_; }
            const Layout& layout() const { return layout_; }
        };
    }
}

#endif /* defined(__OpenGLFramework__element__) */
