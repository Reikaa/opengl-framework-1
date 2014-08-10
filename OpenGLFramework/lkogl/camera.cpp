//
//  camera.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "camera.h"

namespace lkogl {
    namespace camera {
        Camera::Camera(int w, int h) : projection_(60.f, w, h, 1.f, 100.f)
        {}
        
        Camera::~Camera()
        {}
        
        const math::Mat4<float>& Camera::viewMatrix() const
        {
            if(dirty_) {
                viewMatrix_ = math::inverse(math::translate(math::Mat4<float>(), position_) * math::mat4_cast(rotation_));
                dirty_ = false;
            }
            return viewMatrix_;
        }
        
        const math::Vec3<float>& Camera::position() const
        {
            return position_;
        }
        
        void Camera::setPosition(const math::Vec3<float>& p)
        {
            position_ = p;
            dirty_ = true;
        }
        
        const Projection& Camera::projection() const
        {
            return projection_;
        }
        
        Projection& Camera::projection()
        {
            return projection_;
        }
        
        void Camera::lookAt(const math::Vec3<float>& p)
        {
            rotation_ = math::rotation(math::Vec3<float>(0,0,-1), math::normalize(p-position_));
        }
        
    }
}
