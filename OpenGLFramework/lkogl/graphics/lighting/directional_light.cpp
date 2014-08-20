//
//  directional_light.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./directional_light.h"

namespace lkogl {
    namespace graphics {
        namespace lighting {
            
            DirectionalLight::DirectionalLight(math::Vec3<float> color, float intensity, math::Vec3<float> direction)
            :baseLight_(color, intensity), direction_(direction)
            {}
            
            DirectionalLight::~DirectionalLight()
            {}
            
            DirectionalLightUse::DirectionalLightUse(const shader::ProgramUse& program, const DirectionalLight& l)
            {
                program.setUniform("uDirectionalLight.base.color", l.baseLight_.color_);
                program.setUniformf("uDirectionalLight.base.intensity", l.baseLight_.intensity_);
                program.setUniform("uDirectionalLight.direction", l.direction_);
            }
            
            DirectionalLightUse::~DirectionalLightUse() {}
        }
    }
}