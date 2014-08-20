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
#include "program.h"

namespace lkogl {
    namespace graphics {
        namespace lighting {
            class DirectionalLight {
            public:
                BaseLight baseLight_;
                math::Vec3<float> direction_;
                DirectionalLight(math::Vec3<float> color, float intensity, math::Vec3<float> direction);
                ~DirectionalLight();
                
                friend class DirectionalLightUse;
            };
            
            class DirectionalLightUse {
            public:
                DirectionalLightUse(const shader::ProgramUse&, const DirectionalLight&);
                ~DirectionalLightUse();
            };
        }
    }
}

#endif /* defined(__OpenGLFramework__directional_light__) */
