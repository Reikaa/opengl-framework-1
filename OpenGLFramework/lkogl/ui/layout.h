//
//  layout.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 15.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__layout__
#define __OpenGLFramework__layout__

#include "./rectangle.h"
#include "./length.h"
#include "./weight.h"
#include "./space.h"

namespace lkogl {
    namespace ui {
        
        class Layout
        {
            Length width_ = percent(100);
            Length height_ = percent(100);
            WeightPlanar alignment_;
            Space margin_;
            math::Vec2<int> offset_;

            const Layout* parent_ = NULL;
            mutable bool dirty_ = true;
            mutable Rectangle rectangle_;
        public:
            Layout();
            ~Layout();
            
            void setParent(const Layout*);
            
            bool dirty() const;
            void invalidate();
            
            const Rectangle& rectangle() const;

            void setWidth(const Length& w);
            void setHeight(const Length& h);
            void setSize(const Length& w, const Length& h);
            
            const Space& margin() const;
            void setMargin(const Space& space);
            void setAlignment(const WeightPlanar& w);
            
            const math::Vec2<int>& offset() const;
            void setOffset(const math::Vec2<int>& offset);
            void setOffset(const math::Vec2<int>& offset, const Rectangle& clamp);
        private:
            Rectangle::Position calcCenter(const Rectangle::Position& selfSize, const Rectangle::Position& parentSize, int mT, int mR, int mB, int mL) const;
        };
    }
}


#endif /* defined(__OpenGLFramework__layout__) */
