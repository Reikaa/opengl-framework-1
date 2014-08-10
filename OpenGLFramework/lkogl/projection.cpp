//
//  projection.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include <iostream>
#include "projection.h"

namespace lkogl {
    namespace camera {

        Projection::Projection(float fov, int w, int h, float near, float far) :
         fov_(fov), width_(w), height_(h), near_(near), far_(far)
        {
        }
        Projection::~Projection()
        {
        }
            
        const math::Mat4<float>& Projection::matrix() const
        {
            if(dirty_) {
                matrix_ = math::perspective(math::radians(fov_), width_/float(height_), near_, far_);
                dirty_ = false;
            }
            
            return matrix_;
        }
        
        void Projection::setSize(int width, int height)
        {
            width_ = width;
            height_ = height;
            dirty_ = true;
        }
        
        
    }
}