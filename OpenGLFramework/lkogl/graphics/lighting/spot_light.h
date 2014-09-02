//
//  spot_light.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__spot_light__
#define __OpenGLFramework__spot_light__

#include "./point_light.h"

namespace lkogl {
    namespace graphics {
        namespace lighting {
            class SpotLight {
            public:
                PointLight pointLight_;
                math::Vec3<float> direction_;
                float cutoff_;
                
                SpotLight(const math::Vec3<float>& color, float intensity, const math::Vec3<float>& position, const Attenuation& att, const math::Vec3<float>& direction, float cutoff);
                ~SpotLight();
                
                math::elements::Sphere3<float> boundingSphere() const;
                
                friend class PointLightUse;
            };
            
            class SpotLightUse {
            public:
                SpotLightUse(const shader::ProgramUse&, const SpotLight&);
                ~SpotLightUse();
            };
        }
    }
}
#endif /* defined(__OpenGLFramework__spot_light__) */
