//
//  directional_light.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__directional_light__
#define __OpenGLFramework__directional_light__

#include "base_light.h"
#include "shader.h"

namespace lkogl {
    namespace graphics {
        namespace lighting {
            class DirectionalLight {
            public:
                BaseLight baseLight_;
                math::Vec3<float> direction_;
                
                friend class DirectionalLightUse;
            };
            
            class DirectionalLightUse {
            public:
                DirectionalLightUse(const Program&, const DirectionalLight&);
                ~DirectionalLightUse();
            };
        }
    }
}

#endif /* defined(__OpenGLFramework__directional_light__) */
