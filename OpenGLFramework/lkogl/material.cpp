//
//  material.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "material.h"

namespace lkogl {
    namespace graphics {

        Material::Material(Texture texture, float specInt, float specPow) :
        texture_(texture), specularIntensity_(specInt), specularPower_(specPow) {}
        
        Material::Material(Material&& mat) :
            texture_(mat.texture_), specularIntensity_(mat.specularIntensity_), specularPower_(mat.specularPower_)
        {
        }
        
        Material::~Material() {}


        MaterialUse::MaterialUse(const Program& p, const Material& mat) : _texUse(p, mat.texture_)
        {
            glUniform1f(p.handles().specularIntensityPosition, mat.specularIntensity_);
            glUniform1f(p.handles().specularPowerPosition, mat.specularPower_);
        }
        
        MaterialUse::~MaterialUse() {}

    }
}