//
//  spot_light.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./spot_light.h"

namespace lkogl {
    namespace graphics {
        namespace lighting {
            SpotLight::SpotLight(const math::Vec3<float>& color, float intensity, const math::Vec3<float>& position, const Attenuation& att, const math::Vec3<float>& dir, float cut) :
            pointLight_(color, intensity, position, att), direction_(dir), cutoff_(cut)
            {}
            
            SpotLight::~SpotLight()
            {}
            
            
            SpotLightUse::SpotLightUse(const shader::ProgramUse& program, const SpotLight& l)
            {
            
                program.setUniform("uSpotLight.pointLight.baseLight.color", l.pointLight_.baseLight_.color_);
            
                program.setUniformf("uSpotLight.pointLight.baseLight.intensity", l.pointLight_.baseLight_.intensity_);
                
                program.setUniform("uSpotLight.pointLight.position", l.pointLight_.position_);
                program.setUniformf("uSpotLight.pointLight.range", l.pointLight_.range_);
                
                program.setUniformf("uSpotLight.pointLight.attenuation.constant", l.pointLight_.attenuation_.constant_);
                program.setUniformf("uSpotLight.pointLight.attenuation.linear", l.pointLight_.attenuation_.linear_);
                program.setUniformf("uSpotLight.pointLight.attenuation.quadratic", l.pointLight_.attenuation_.quadratic_);

                program.setUniform("uSpotLight.direction", l.direction_);
                program.setUniformf("uSpotLight.cutoff", l.cutoff_);
            }
            
            SpotLightUse::~SpotLightUse()
            {}
        }
    }
}