//
//  transform.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 08.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./transformation.h"

namespace lkogl {
    namespace geometry {
        const Transformation::Mat4 Transformation::matrix() const
        {
            Mat4 result = math::translate(Mat4(), translation_);
            result = math::rotate(result, rotation_);
            result = math::scale(result, scale_);

            return result;
        }
        
        void Transformation::transform(const Transformation& t) {
            rotation_ = math::normalize(rotation_*t.rotation_);
            scale_ *= t.scale_;
            translation_ += t.translation_;
        }
    }
}