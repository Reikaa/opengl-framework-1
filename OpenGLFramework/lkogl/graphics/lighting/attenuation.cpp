//
//  attenuation.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//


#include "../../math/base.h"
#include "./attenuation.h"

namespace lkogl {
    namespace graphics {
        namespace lighting {
            Attenuation::Attenuation(float c, float l, float q) :
            constant_(c), linear_(l), quadratic_(q)
            {}
                
            float Attenuation::calc(float x) const
            {
                return quadratic_ * x*x + linear_ * x + constant_;
            }
            
            float Attenuation::solve(float y) const
            {
                float c = constant_ - y;
                float a = quadratic_;
                float b = linear_;
                
                // abc formula
                return (-b+sqrtf(b*b-4*a*c))/(2*a);
            }
        }
    }
}