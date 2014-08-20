//
//  material.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./material.h"

namespace lkogl {
    namespace graphics {

        Material::Material(Texture texture, float specInt, float specPow) :
        texture_(texture), specularIntensity_(specInt), specularPower_(specPow) {}
        
        Material::Material(const Material& mat) :
            texture_(mat.texture_), specularIntensity_(mat.specularIntensity_), specularPower_(mat.specularPower_)
        {
        }
        
        Material::~Material() {}


        MaterialUse::MaterialUse(const shader::ProgramUse& p, const Material& mat) : _texUse(p, mat.texture_)
        {
            p.setUniformf("material.specularIntensity", mat.specularIntensity_);
            p.setUniformf("material.specularPower", mat.specularPower_);
        }
        
        MaterialUse::~MaterialUse() {}

    }
}