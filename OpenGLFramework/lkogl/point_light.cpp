//
//  point_light.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "point_light.h"

namespace lkogl {
    namespace graphics {
        namespace lighting {
            constexpr int COLOR_DEPTH = 256;
            
            PointLight::PointLight(const math::Vec3<float>& color, float intensity, const math::Vec3<float>& position, const Attenuation& att) :
            baseLight_(color, intensity),
            position_(position),
            attenuation_(att),
            range_(att.solve(intensity*math::max(color)*COLOR_DEPTH))
            {}
            
            PointLight::~PointLight()
            {}
            

            PointLightUse::PointLightUse(const Program& program, const PointLight& l)
            {
                glUniform3f(program.handles().pointLightColorPosition, l.baseLight_.color_.x, l.baseLight_.color_.y, l.baseLight_.color_.z);
                glUniform1f(program.handles().pointLightIntensityPosition, l.baseLight_.intensity_);
                
                glUniform3f(program.handles().pointLightPositionPosition, l.position_.x, l.position_.y, l.position_.z);
                glUniform1f(program.handles().pointLightRangePosition, l.range_);
                
                glUniform1f(program.handles().pointLightAttenuationCPosition, l.attenuation_.constant_);
                glUniform1f(program.handles().pointLightAttenuationLPosition, l.attenuation_.linear_);
                glUniform1f(program.handles().pointLightAttenuationQPosition, l.attenuation_.quadratic_);
            }
            
            PointLightUse::~PointLightUse()
            {}
        }
    }
}