//
//  space.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 16.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__space__
#define __OpenGLFramework__space__

#include <stdio.h>
#include "./length.h"

namespace lkogl {
    namespace ui {
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
                        
            // operators
            
            Space operator+= (const Space& b);
            
            Space operator-= (const Space& b);
        };
        
        Space operator+(const Space& a, const Space& b);
        
        Space operator-(const Space& a, const Space& b);
        
    }
}

#endif /* defined(__OpenGLFramework__space__) */
