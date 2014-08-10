//
//  transform.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 08.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "transform.h"
#include <iostream>

namespace lkogl {
    namespace geometry {
        const Transform::Mat4 Transform::matrix() const
        {
            Mat4 result = math::translate(Mat4(), translation);
            result = math::scale(result, scale);
            result = math::rotate(result, rotation);

            return result;
        }
    }
}