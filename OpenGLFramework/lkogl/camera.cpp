//
//  camera.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "camera.h"
#include <iostream>

namespace lkogl {
    namespace camera {
        Camera::Camera(int w, int h) : projection_(70.f, 16, 9, 0.1f, 100.f)
        {
        }
        
        Camera::~Camera()
        {}
        
        const math::Mat4<float>& Camera::viewMatrix() const
        {
            return viewMatrix_;
        }
        
        const Projection& Camera::projection() const
        {
            return projection_;
        }
        
        const math::Vec3<float>& Camera::position() const
        {
            return position_;
        }
        
        const math::Mat4<float>& Camera::viewProjectionMatrix() const
        {
            if(dirtyViewProjection_) {
                viewProjectionMatrix_ = projection_.matrix() * viewMatrix_;
                dirtyViewProjection_ = false;
            }
            return viewProjectionMatrix_;
        }
        
        void Camera::setProjection(const Projection& proj)
        {
            projection_ = proj;
        }
        
        void Camera::setViewMatrix(const math::Mat4<float> & matrix)
        {
            viewMatrix_ = matrix;
            position_ = -math::Vec3<float>(matrix[4][0]);
            dirtyViewProjection_ = true;
        }
        
    }
}
