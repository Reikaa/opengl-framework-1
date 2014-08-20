//
//  length.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 16.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./length.h"

namespace lkogl {
    namespace ui {
        
        const Length px(int p) { return Length(p, 0); }
        const Length percent(int p) { return Length(0, 0.01*p); }
        const Length fill(int p) { return Length(-p, 1); }

        Length Length::operator+= (const Length& b) {
            abs_ += b.abs_;
            rel_ += b.rel_;
            
            return *this;
        };
        
        Length Length::operator-= (const Length& b) {
            abs_ -= b.abs_;
            rel_ -= b.rel_;
            
            return *this;
        };
        
        Length operator+ (const Length& a, const Length& b) {
            return Length(a)+=b;
        };
        
        Length operator- (const Length& a, const Length& b) {
            return Length(a)-=b;
        };
    }
}