//
//  spot_light.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "spot_light.h"

namespace lkogl {
    namespace graphics {
        namespace lighting {
            SpotLight::SpotLight(const math::Vec3<float>& color, float intensity, const math::Vec3<float>& position, const Attenuation& att, const math::Vec3<float>& dir, float cut) :
            pointLight_(color, intensity, position, att), direction_(dir), cutoff_(cut)
            {}
            
            SpotLight::~SpotLight()
            {}
            
            
            SpotLightUse::SpotLightUse(const Program& program, const SpotLight& l)
            {
                glUniform3f(program.handles().spotLightColorPosition, l.pointLight_.baseLight_.color_.x, l.pointLight_.baseLight_.color_.y, l.pointLight_.baseLight_.color_.z);
                glUniform1f(program.handles().spotLightIntensityPosition, l.pointLight_.baseLight_.intensity_);
                
                glUniform3f(program.handles().spotLightPositionPosition, l.pointLight_.position_.x, l.pointLight_.position_.y, l.pointLight_.position_.z);
                glUniform1f(program.handles().spotLightRangePosition, l.pointLight_.range_);
                
                glUniform1f(program.handles().spotLightAttenuationCPosition, l.pointLight_.attenuation_.constant_);
                glUniform1f(program.handles().spotLightAttenuationLPosition, l.pointLight_.attenuation_.linear_);
                glUniform1f(program.handles().spotLightAttenuationQPosition, l.pointLight_.attenuation_.quadratic_);
                
                glUniform3f(program.handles().spotLightDirectionPosition, l.direction_.x, l.direction_.y, l.direction_.z);
                glUniform1f(program.handles().spotLightCutoffPosition, l.cutoff_);
            }
            
            SpotLightUse::~SpotLightUse()
            {}
        }
    }
}