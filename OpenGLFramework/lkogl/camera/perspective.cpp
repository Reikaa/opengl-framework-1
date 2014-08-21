//
//  projection.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./perspective.h"

namespace lkogl {
    namespace camera {

        Perspective::Perspective(float fov, int w, int h, float near, float far) :
         frustum_(math::radians(fov), w, h, near, far)
        {
        }
        Perspective::~Perspective()
        {
        }
            
        const math::Mat4<float>& Perspective::matrix() const
        {
            if(dirty_) {
                matrix_ = math::geo::mat_cast(frustum_);
                dirty_ = false;
            }
            
            return matrix_;
        }
        
        const math::geo::Frustum3<float>& Perspective::frustum() const
        {
            return frustum_;
        }
        
        
    }
}