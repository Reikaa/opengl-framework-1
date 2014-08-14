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
            math::Mat4<float> viewMatrix_;
            Projection projection_;

            mutable bool dirtyViewProjection_ = true;
            mutable math::Mat4<float> viewProjectionMatrix_;
            mutable math::Vec3<float> position_;
            
        public:
            Camera(int w, int h);
            ~Camera();
            
            void setViewMatrix(const math::Mat4<float>&);

            const math::Mat4<float>& viewMatrix() const;
            const math::Vec3<float>& position() const;
            const Projection& projection() const;
            const math::Mat4<float>& viewProjectionMatrix() const;
            void setProjection(const Projection& proj);
        };
    }
}

#endif /* defined(__OpenGLFramework__camera__) */
