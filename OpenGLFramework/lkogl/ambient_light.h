//
//  ambient_light.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__ambient_light__
#define __OpenGLFramework__ambient_light__

#include <stdio.h>
#include "math.h"
#include "program.h"

namespace lkogl {
    namespace graphics {
        namespace lighting {
            class AmbientLight {
                math::Vec3<float> intensity_;
            public:
                AmbientLight(const math::Vec3<float> intensity);
                ~AmbientLight();
                friend class AmbientLightUse;
            };
            
            class AmbientLightUse {
            public:
                AmbientLightUse(const Program&, const AmbientLight&);
                ~AmbientLightUse();
            
            };
        }
    }
}

#endif /* defined(__OpenGLFramework__ambient_light__) */
