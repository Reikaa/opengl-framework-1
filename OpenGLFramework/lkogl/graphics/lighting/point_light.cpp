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
            constexpr int COLOR_DEPTH = 256;
            
            PointLight::PointLight(const math::Vec3<float>& color, float intensity, const math::Vec3<float>& position, const Attenuation& att) :
            baseLight_(color, intensity),
            position_(position),
            attenuation_(att),
            range_(att.solve(intensity*math::max(color)*COLOR_DEPTH))
            {}
            
            PointLight::~PointLight()
            {}
            

            PointLightUse::PointLightUse(const shader::ProgramUse& program, const PointLight& l)
            {
                
                program.setUniform("", l.baseLight_.color_);
                program.setUniformf("", l.baseLight_.intensity_);
                program.setUniform("", l.position_);
                program.setUniformf("", l.range_);
                
                program.setUniformf("", l.attenuation_.constant_);
                program.setUniformf("", l.attenuation_.linear_);
                program.setUniformf("", l.attenuation_.quadratic_);
            }
            
            PointLightUse::~PointLightUse()
            {}
        }
    }
}