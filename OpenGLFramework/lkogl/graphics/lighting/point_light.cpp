//
//  point_light.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./point_light.h"

namespace lkogl {
    namespace graphics {
        namespace lighting {
            constexpr int COLOR_DEPTH = 32;
            
            PointLight::PointLight(const math::Vec3<float>& color, float intensity, const math::Vec3<float>& position, const Attenuation& att) :
            baseLight_(color, intensity),
            position_(position),
            attenuation_(att),
            range_(att.solve(intensity*math::max(color)*COLOR_DEPTH))
            {}
            
            PointLight::~PointLight()
            {}
            
            math::elements::Sphere3<float> PointLight::boundingSphere() const
            {
                return math::elements::Sphere3<float>(position_, range_);
            }
            

            PointLightUse::PointLightUse(const shader::ProgramUse& program, const PointLight& l)
            {
                
                program.setUniform("uPointLight.baseLight.color", l.baseLight_.color_);
                
                program.setUniformf("uPointLight.baseLight.intensity", l.baseLight_.intensity_);
                
                program.setUniform("uPointLight.position", l.position_);
                program.setUniformf("uPointLight.range", l.range_);
                
                program.setUniformf("uPointLight.attenuation.constant", l.attenuation_.constant_);
                program.setUniformf("uPointLight.attenuation.linear", l.attenuation_.linear_);
                program.setUniformf("uPointLight.attenuation.quadratic", l.attenuation_.quadratic_);
            }
            
            PointLightUse::~PointLightUse()
            {}
        }
    }
}