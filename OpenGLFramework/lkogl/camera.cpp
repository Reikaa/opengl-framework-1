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
        Camera::Camera(int w, int h) : perspective_(70.f, 16, 9, 0.1f, 500.f)
        {
        }
        
        Camera::~Camera()
        {}
        
        const math::Mat4<float>& Camera::viewMatrix() const
        {
            return viewMatrix_;
        }
        
        const Perspective& Camera::perspective() const
        {
            return perspective_;
        }
        
        const math::Vec3<float>& Camera::position() const
        {
            return position_;
        }
        
        const math::Mat4<float>& Camera::viewProjectionMatrix() const
        {
            if(dirtyViewProjection_) {
                viewProjectionMatrix_ = perspective_.matrix() * viewMatrix_;
                dirtyViewProjection_ = false;
            }
            return viewProjectionMatrix_;
        }
        
        void Camera::setProjection(const Perspective& persp)
        {
            perspective_ = persp;
        }
        
        void Camera::setViewMatrixAndPos(const math::Mat4<float> & matrix, const math::Vec3<float>& pos)
        {
            viewMatrix_ = matrix;
            position_ = pos;
            dirtyViewProjection_ = true;
        }
        
    }
}
