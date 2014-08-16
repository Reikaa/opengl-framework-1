//
//  projection.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__projection__
#define __OpenGLFramework__projection__

#include "math.h"

namespace lkogl {
    namespace camera {
        class Projection {
            mutable math::Mat4<float> matrix_;
            mutable bool dirty_ = true;
            
            int width_;
            int height_;
            float near_;
            float far_;
            float fov_;
            
        public:
            
            Projection(float fov, int w, int h, float near, float far);
            ~Projection();
            
            const math::Mat4<float>& matrix() const;
            void setSize(int width, int height);
            
            float far() const { return far_; }
        };
    }
}

#endif /* defined(__OpenGLFramework__projection__) */
