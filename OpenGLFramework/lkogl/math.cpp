//
//  math.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "math.h"

namespace lkogl {
    namespace math {
        float radians(const int& deg) {
            return deg * 2 * M_PI / 360.f;
        }
    }
}