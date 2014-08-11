//
//  directional_light.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "directional_light.h"

namespace lkogl {
    namespace graphics {
        namespace lighting {
            
            DirectionalLight::DirectionalLight(math::Vec3<float> color, float intensity, math::Vec3<float> direction)
            :baseLight_(color, intensity), direction_(direction)
            {}
            
            DirectionalLight::~DirectionalLight()
            {}
            
            DirectionalLightUse::DirectionalLightUse(const Program& program, const DirectionalLight& l)
            {
                glUniform3f(program.handles().directionalLightColorPosition, l.baseLight_.color_.x, l.baseLight_.color_.y, l.baseLight_.color_.z);
                glUniform1f(program.handles().directionalLightIntensityPosition, l.baseLight_.intensity_);
                glUniform3f(program.handles().directionalLightDirectionPosition, l.direction_.x, l.direction_.y, l.direction_.z);
            }
            
            DirectionalLightUse::~DirectionalLightUse() {}
        }
    }
}