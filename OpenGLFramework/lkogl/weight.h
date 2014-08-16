//
//  weight.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 16.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__weight__
#define __OpenGLFramework__weight__

#include <stdio.h>

namespace lkogl {
    namespace ui {
    
        class WeightLinear {
            const int a_;
            const int b_;
            WeightLinear(int a, int b) : a_(a), b_(b)
            {}
        public:
            static WeightLinear Center;
            
            static WeightLinear Left;
            static WeightLinear Right;
            
            static WeightLinear Top;
            static WeightLinear Bottom;
            
            friend class WeightPlanar;
        };
        
        class WeightPlanar {
        private:
            int left_;
            int right_;
            int top_;
            int bottom_;
        public:
            WeightPlanar(const WeightLinear& v, const WeightLinear& h) :
            left_(v.a_), right_(v.b_),
            top_(h.a_), bottom_(h.b_)
            {}
            
            WeightPlanar() : WeightPlanar(WeightLinear::Left, WeightLinear::Top)
            {}
            
            friend class Layout;
        };
        
    }
}

#endif /* defined(__OpenGLFramework__weight__) */
