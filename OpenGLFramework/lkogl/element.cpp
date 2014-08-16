//
//  element.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 15.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "element.h"

namespace lkogl {
    namespace ui {
        Element::Element() {
        }
        
        Element::Element(Length w, Length h)
        {
            layout_.setWidth(w);
            layout_.setHeight(h);
        }
        
        Element::~Element() {
        }
        
        void Element::addChild(std::shared_ptr<Element> n) {
            n->layout_.setParent(&layout_);
            children_.push_back(n);
        }
        
        void Element::removeChild(std::shared_ptr<Element> n) {
            children_.remove(n);
        }
        
        const std::list<std::shared_ptr<Element>>& Element::children() const
        {
            return children_;
        }
    }
}