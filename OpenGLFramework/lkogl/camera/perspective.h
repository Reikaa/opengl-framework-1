//
//  projection.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__projection__
#define __OpenGLFramework__projection__

#include "../math/math.h"
#include "../math/elements.h"

namespace lkogl {
    namespace camera {
        class Perspective {
            mutable math::Mat4<float> matrix_;
            mutable bool dirty_ = true;
            
            math::elements::Frustum3<float> frustum_;
        public:
            
            Perspective(float fov, int w, int h, float near, float far);
            ~Perspective();
            
            const math::Mat4<float>& matrix() const;
            const math::elements::Frustum3<float>& frustum() const;
            
            float far() const { return frustum_.planes.far.constant; }
        };
    }
}

#endif /* defined(__OpenGLFramework__projection__) */
