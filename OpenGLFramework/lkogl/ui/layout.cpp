//
//  layout.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 15.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./layout.h"

#include <iostream>

namespace lkogl {
    namespace ui {
        Layout::Layout()
        {
        }
        
        Layout::~Layout()
        {
        }
                
        void Layout::setParent(const Layout* parent)
        {
            parent_ = parent;
            dirty_ = true;
        }
        
        const Space& Layout::margin() const
        {
            return margin_;
        }
        
        void Layout::setMargin(const Space& space)
        {
            margin_ = space;
            dirty_ = true;
        }
        
        
        void Layout::setAlignment(const WeightPlanar& weight)
        {
            alignment_ = weight;
            dirty_ = true;
        }
        
        void Layout::setWidth(const Length& w)
        {
            width_ = w;
            dirty_ = true;
        }
        
        void Layout::setHeight(const Length& h)
        {
            height_ = h;
            dirty_ = true;
        }
        
        void Layout::setSize(const lkogl::ui::Length &w, const lkogl::ui::Length &h)
        {
            height_ = h;
            width_ = w;
            dirty_ = true;
        }
        
        bool Layout::overflow() const
        {
            return overflow_;
        }
        
        void Layout::setOverflow(bool col)
        {
            overflow_ = col;
        }
        
        const math::Vec2<int>& Layout::offset() const
        {
            return offset_;
        }
        
        void Layout::setOffset(const math::Vec2<int>& offset)
        {
            offset_ = offset;
            dirty_ = true;
        }
        
        void Layout::setOffset(const math::Vec2<int>& offset, const Rectangle& clamp)
        {
            Rectangle ownRect = rectangle();
            math::Vec2<int> offsetDiff = offset - offset_;
            
            math::Vec2<int> minDiff = offsetDiff + ownRect.topLeft() - clamp.topLeft();
            math::Vec2<int> maxDiff = offsetDiff + ownRect.bottomRight() - clamp.bottomRight();
            
            if(minDiff.x < 0) {
                offsetDiff.x -= minDiff.x;
            }
            if(maxDiff.x > 0) {
                offsetDiff.x -= maxDiff.x;
            }
            
            if(minDiff.y < 0) {
                offsetDiff.y -= minDiff.y;
            }
            if(maxDiff.y > 0) {
                offsetDiff.y -= maxDiff.y;
            }
            
            offset_ += offsetDiff;
            
            dirty_ = true;
        }
        
        bool Layout::dirty() const
        {
            return dirty_ || (parent_!=0 && parent_->dirty());
        }
        
        void Layout::invalidate()
        {
            dirty_ = true;
        }
        
        const Rectangle& Layout::rectangle() const
        {
            if(dirty()) {
                Rectangle parentRect;
                if(parent_ != 0) parentRect = parent_->rectangle();
                
                int mT = margin_.top.calc(parentRect.height());
                int mR = margin_.right.calc(parentRect.width());
                int mB = margin_.bottom.calc(parentRect.height());
                int mL = margin_.left.calc(parentRect.width());
                
                rectangle_.setSize(width_.calc(parentRect.width()-mR-mL), height_.calc(parentRect.height()-mT-mB));
                
                math::Vec2<int> parentSize = math::max(parentRect.size(), rectangle_.size());
                
                rectangle_.setCenter(offset_ + parentRect.topLeft() + calcCenter({rectangle_.width(), rectangle_.height()}, {parentSize.x,parentSize.y}, mT, mR, mB, mL));

                dirty_ = false;
            }
            
            return rectangle_;
        }
        
        Rectangle::Position Layout::calcCenter(const Rectangle::Position& selfSize, const Rectangle::Position& parentSize, int mT, int mR, int mB, int mL) const {
            return {
                (alignment_.left_ * mL
                 + alignment_.right_ * (parentSize.x - (selfSize.x + mR)))
                / (alignment_.left_+alignment_.right_)
                + selfSize.x/2,
                
                (alignment_.top_ * mT
                 + alignment_.bottom_ * (parentSize.y - (selfSize.y + mB)))
                / (alignment_.top_+alignment_.bottom_)
                + selfSize.y/2
            };
        }
    }
}