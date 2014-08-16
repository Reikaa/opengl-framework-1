//
//  layout.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 15.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include <iostream>
#include "layout.h"

namespace lkogl {
    namespace ui {
        
        Weight Weight::Center{1,1};
        Weight Weight::Left{1,0};
        Weight Weight::Right{0,1};
        
        Weight Weight::Top{1,0};
        Weight Weight::Bottom{0,1};
        
        const Length px(int p) { return Length(p, 0); }
        const Length percent(int p) { return Length(0, 0.01*p); }
        const Length fill(int p) { return Length(-p, 1); }
        
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
        
        void Layout::setMargin(const Space& space)
        {
            alignment_.margin = space;
            dirty_ = true;
        }
        
        void Layout::setAlignment(const Weight2D& weight)
        {
            alignment_.weight = weight;
            dirty_ = true;
        }
        
        const Rectangle& Layout::rectangle() const
        {
            if(dirty_) {
                Rectangle parentRect;
                if(parent_ != 0) parentRect = parent_->rectangle();
                
                int mT = alignment_.margin.top.calc(parentRect.height());
                int mR = alignment_.margin.right.calc(parentRect.width());
                int mB = alignment_.margin.bottom.calc(parentRect.height());
                int mL = alignment_.margin.left.calc(parentRect.width());
                
                rectangle_.setSize(width_.calc(parentRect.width()-mR-mL), height_.calc(parentRect.height()-mT-mB));
                
                math::Vec2<int> parentSize = math::max(parentRect.size(), rectangle_.size());
                
                std::cout << math::toString(parentSize) << std::endl;
                
                rectangle_.setCenter(parentRect.topLeft() + calcCenter({rectangle_.width(), rectangle_.height()}, {parentSize.x,parentSize.y}, mT, mR, mB, mL));
                
                dirty_ = false;
            }
            
            return rectangle_;
        }
        
        Rectangle::Position Layout::calcCenter(const Rectangle::Position& selfSize, const Rectangle::Position& parentSize, int mT, int mR, int mB, int mL) const {
            return {
                (alignment_.weight.left_ * mL
                 + alignment_.weight.right_ * (parentSize.x - (selfSize.x + mR)))
                / (alignment_.weight.left_+alignment_.weight.right_)
                + selfSize.x/2,
                
                (alignment_.weight.top_ * mT
                 + alignment_.weight.bottom_ * (parentSize.y - (selfSize.y + mB)))
                / (alignment_.weight.top_+alignment_.weight.bottom_)
                + selfSize.y/2
            };
        }
    }
}