//
//  ambient_light.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./ambient_light.h"

namespace lkogl {
    namespace graphics {
        namespace lighting {

            AmbientLight::AmbientLight(const math::Vec3<float> intensity) :
            intensity_(intensity)
            {}
            AmbientLight::~AmbientLight()
            {}

            
            AmbientLightUse::AmbientLightUse(const shader::ProgramUse& program, const AmbientLight& amb)
            {
                program.setUniform("uAmbientIntensity", amb.intensity_);
            }
            
            AmbientLightUse::~AmbientLightUse()
            {}
   
        }
    }
}
