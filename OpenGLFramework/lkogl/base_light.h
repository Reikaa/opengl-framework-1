//
//  base_light.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__base_light__
#define __OpenGLFramework__base_light__

#include "math.h"

namespace lkogl {
    namespace graphics {
        namespace lighting {
            class BaseLight {
            public:
                math::Vec3<float> color_;
                float intensity_;
            };
        }
    }
}

#endif /* defined(__OpenGLFramework__base_light__) */
