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
        
        Element::Element(const std::shared_ptr<Behaviour> b) : behaviour_(b)
        {
            behaviour_->onInit(*this);
        }
        
        Element::~Element()
        {
        }
        
        void Element::addChild(std::shared_ptr<Element> n)
        {
            n->layout_.setParent(&layout_);
            children_.push_back(n);
        }
        
        void Element::removeChild(std::shared_ptr<Element> n)
        {
            children_.remove(n);
        }
        
        const std::list<std::shared_ptr<Element>>& Element::children() const
        {
            return children_;
        }
        
        Layout& Element::layout()
        {
            return layout_;
        }
        
        const Layout& Element::layout() const
        {
            return layout_;
        }
        
        const Style& Element::style() const
        {
            return style_;
        }
        
        Style& Element::style()
        {
            return style_;
        }
        
        bool Element::render() const
        {
            return true;
        }
        
        bool Element::onFocus()
        {
            if(behaviour_.get() != 0) {
                return behaviour_->onFocus(*this);
            }
            return true;
        }
        
        bool Element::onBlur()
        {
            if(behaviour_.get() != 0) {
                return behaviour_->onBlur(*this);
            }
            return true;
        }
        
        bool Element::onContactBegin(const math::Vec2<int>& pos)
        {
            if(behaviour_.get() != 0) {
                return behaviour_->onContactBegin(*this, pos);
            }
            return true;
        }
        
        bool Element::onContactEnd(const math::Vec2<int>& pos)
        {
            if(behaviour_.get() != 0) {
                return behaviour_->onContactEnd(*this, pos);
            }
            return true;
        }
        
        bool Element::onContactMove(const math::Vec2<int>& pos)
        {
            if(behaviour_.get() != 0) {
                return behaviour_->onContactMove(*this, pos);
            }
            return true;
        }
        
        bool Element::onContactCancel()
        {
            if(behaviour_.get() != 0) {
                return behaviour_->onContactCancel(*this);
            }
            return true;
        }
    }
}