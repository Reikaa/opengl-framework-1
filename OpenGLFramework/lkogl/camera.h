//
//  camera.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__camera__
#define __OpenGLFramework__camera__

#include "math.h"
#include "projection.h"

namespace lkogl {
    namespace camera {
        class Camera {
            mutable bool dirtyView_ = true;
            mutable math::Mat4<float> viewMatrix_;
            
            mutable bool dirtyProjection_ = true;
            mutable math::Mat4<float> viewProjectionMatrix_;
            
        public:
            Projection projection_;
            math::Quat<float> rotation_;
            math::Vec3<float> position_;
            
            Camera(int w, int h);
            ~Camera();
            
            const math::Mat4<float>& viewMatrix() const;
            const math::Mat4<float>& viewProjectionMatrix() const;
            void setProjection(const Projection& proj);
            
            const math::Vec3<float>& position() const;
            const math::Quat<float>& rotation() const;
            void setPosition(const math::Vec3<float>& pos);
            void setRotation(const math::Quat<float>& rot);
            void lookAt(const math::Vec3<float>& p);
        };
    }
}

#endif /* defined(__OpenGLFramework__camera__) */
