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

        Material::Material(Texture texture, Texture normalMap, float specInt, float specPow) :
        texture_(texture), specularIntensity_(specInt), specularPower_(specPow), normalMap_(normalMap) {}
        
        Material::Material(const Material& mat) :
            texture_(mat.texture_), specularIntensity_(mat.specularIntensity_), specularPower_(mat.specularPower_), normalMap_(mat.normalMap_)
        {
        }
        
        Material::~Material() {}


        MaterialUse::MaterialUse(const shader::ProgramUse& p, const Material& mat) : texUse_(p,"uMaterial.color", mat.texture_, 0), texNormalUse_(p,"uMaterial.normal", mat.normalMap_, 1)
        {
            p.setUniformf("uMaterial.specularIntensity", mat.specularIntensity_);
            p.setUniformf("uMaterial.specularPower", mat.specularPower_);
            p.setUniform("uMaterial.coloring", math::Vec4<float>(0,0,0,0));
        }
        
        MaterialUse::~MaterialUse() {}

    }
}