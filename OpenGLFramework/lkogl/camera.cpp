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
        Camera::Camera(int w, int h) : projection_(70.f, 16, 9, .8f, 100.f)
        {
        }
        
        Camera::~Camera()
        {}
        
        const math::Mat4<float>& Camera::viewMatrix() const
        {
            if(dirtyView_) {
                viewMatrix_ = math::inverse(math::translate(math::Mat4<float>(), position_) * math::mat4_cast(rotation_));
                dirtyView_ = false;
            }
            return viewMatrix_;
        }
        
        const math::Mat4<float>& Camera::viewProjectionMatrix() const
        {
            if(dirtyView_ || dirtyProjection_) {
                viewProjectionMatrix_ = projection_.matrix() * viewMatrix();
                dirtyProjection_ = false;
            }
            return viewProjectionMatrix_;
        }
        
        const math::Vec3<float>& Camera::position() const
        {
            return position_;
        }
        
        const math::Quat<float>& Camera::rotation() const
        {
            
            return rotation_;
        }
        
        void Camera::setPosition(const math::Vec3<float>& p)
        {
            position_ = p;
            dirtyView_ = true;
        }
        
        void Camera::setRotation(const math::Quat<float>& r)
        {
            rotation_ = r;
            dirtyView_ = true;
        }
                
        void Camera::setProjection(const Projection& proj)
        {
            projection_ = proj;
        }
        
        void Camera::lookAt(const math::Vec3<float>& p)
        {
            rotation_ = math::rotation(math::Vec3<float>(0,0,-1), math::normalize(p-position_));
        }
        
    }
}
