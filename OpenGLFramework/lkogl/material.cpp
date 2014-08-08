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

        Material::Material(Program program, std::vector<Texture> textures) :
        program_(std::move(program)), textures_(std::move(textures)) {}
        
        Material::Material(Material&& mat) :
            program_(std::move(mat.program_)),
            textures_(std::move(mat.textures_))
        {
        }
        
        Material::~Material() {}


        MaterialUse::MaterialUse(const Material& material) : p(material.program())
        {}
        
        MaterialUse::~MaterialUse() {}

    }
}