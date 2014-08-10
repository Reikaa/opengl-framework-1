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

        Material::Material(std::vector<Texture> textures) :
        textures_(std::move(textures)) {}
        
        Material::Material(Material&& mat) :
            textures_(std::move(mat.textures_))
        {
        }
        
        Material::~Material() {}


        MaterialUse::MaterialUse(const Material& material)
        {}
        
        MaterialUse::~MaterialUse() {}

    }
}