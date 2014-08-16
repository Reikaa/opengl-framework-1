//
//  layout.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 15.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__layout__
#define __OpenGLFramework__layout__

#include "rectangle.h"

namespace lkogl {
    namespace ui {
        class Length {
            float abs_;
            float rel_;
        public:
            
            int calc(int par) const {
                return abs_+rel_*par;
            }
            Length(int length) : abs_(length), rel_(0)
            {}
            Length() : abs_(1), rel_(0)
            {}
        private:
            Length(float abs, float rel) : abs_(abs), rel_(rel)
            {}
            friend const Length px(int p);
            friend const Length percent(int p);
            friend const Length fill(int p);
        };
        
        const Length px(int p);
        const Length percent(int p);
        const Length fill(int p);
        
        struct Space
        {
            Length top;
            Length right;
            Length bottom;
            Length left;
            
            Space() {}
            Space(const Length& one) : top(one),right(one), bottom(one), left(one) {}
            Space(const Length& one, const Length& two) : top(one),right(two), bottom(one), left(two) {}
            Space(const Length& one, const Length& two, const Length& three) : top(one),right(two), bottom(three), left(two) {}
            Space(const Length& one, const Length& two, const Length& three, const Length& four) : top(one),right(two), bottom(three), left(four) {}
        };
        
        class Weight {
            const int a_;
            const int b_;
            Weight(int a, int b) : a_(a), b_(b)
            {}
        public:
            static Weight Center;
            
            static Weight Left;
            static Weight Right;
            
            static Weight Top;
            static Weight Bottom;
            
            friend class Weight2D;
        };
        
        class Weight2D {
        private:
            int left_;
            int right_;
            int top_;
            int bottom_;
        public:
            Weight2D(Weight v, Weight h) :
                left_(v.a_), right_(v.b_),
                top_(h.a_), bottom_(h.b_)
            {}
            
            friend class Layout;
        };
        
        class Alignment {
        public:
            Space margin;
            Weight2D weight = Weight2D(Weight::Left, Weight::Top);
        };
        
        class Layout
        {
            Length width_;
            Length height_;
            Alignment alignment_;
            const Layout* parent_ = NULL;
            mutable bool dirty_ = true;
            mutable Rectangle rectangle_;
        public:
            Layout();
            ~Layout();
            
            void setParent(const Layout*);
            
            const Rectangle& rectangle() const;
            
            void setWidth(Length w) { width_ = w; }
            void setHeight(Length h) { height_ = h; }
            
            void setMargin(const Space& space);
            void setAlignment(const Weight2D& w);
            
        private:
            Rectangle::Position calcCenter(const Rectangle::Position& selfSize, const Rectangle::Position& parentSize, int mT, int mR, int mB, int mL) const;
        };
    }
}


#endif /* defined(__OpenGLFramework__layout__) */
