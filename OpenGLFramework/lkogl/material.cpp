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

        Material::Material(const Program&, const std::vector<Texture>&) {}
        Material::~Material() {}


        MaterialUse::MaterialUse(const Material&) {}
        MaterialUse::~MaterialUse() {}

    }
}