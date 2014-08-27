//
//  point_light.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__point_light__
#define __OpenGLFramework__point_light__

#include "../../math/elements.h"

#include "./base_light.h"
#include "./attenuation.h"
#include "../shader/program.h"

namespace lkogl {
    namespace graphics {
        namespace lighting {
            class PointLight {
            public:
                BaseLight baseLight_;
                math::Vec3<float> position_;
                Attenuation attenuation_;
                float range_;
                
                PointLight(const math::Vec3<float>& color, float intensity, const math::Vec3<float>& position, const Attenuation& att);
                ~PointLight();
                
                math::geo::Sphere3<float> boundingSphere() const;
                
                friend class PointLightUse;
            };
            
            class PointLightUse {
            public:
                PointLightUse(const shader::ProgramUse&, const PointLight&);
                ~PointLightUse();
            };
        }
    }
}

#endif /* defined(__OpenGLFramework__point_light__) */
