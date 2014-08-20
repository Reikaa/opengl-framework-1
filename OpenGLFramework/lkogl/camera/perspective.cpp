//
//  projection.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "perspective.h"

namespace lkogl {
    namespace camera {

        Perspective::Perspective(float fov, int w, int h, float near, float far) :
         fov_(fov), width_(w), height_(h), near_(near), far_(far)
        {
        }
        Perspective::~Perspective()
        {
        }
            
        const math::Mat4<float>& Perspective::matrix() const
        {
            if(dirty_) {
                matrix_ = math::perspective(math::radians(fov_), width_/float(height_), near_, far_);
                dirty_ = false;
            }
            
            return matrix_;
        }
        
        
    }
}