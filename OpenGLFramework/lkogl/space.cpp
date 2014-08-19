//
//  space.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 16.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "space.h"

namespace lkogl {
    namespace ui {
        
        Space Space::operator+= (const Space& b) {
            top += b.top;
            right += b.right;
            bottom += b.bottom;
            left += b.left;
            
            return *this;
        };
        
        Space Space::operator-= (const Space& b) {
            top -= b.top;
            right -= b.right;
            bottom -= b.bottom;
            left -= b.left;
            
            return *this;
        };
        
        Space operator+(const Space& a, const Space& b) {
            return Space(a)+=b;
        }
        
        Space operator-(const Space& a, const Space& b) {
            return Space(a)-=b;
        }
    }
}