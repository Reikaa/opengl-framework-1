//
//  material.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__material__
#define __OpenGLFramework__material__

#include <vector>

#include "texture.h"
#include "shader.h"

namespace lkogl {
    namespace graphics {
        class Material {
            std::vector<Texture> textures_;
        public:
            Material() = delete;
            Material(Material&& mat);
            Material(const std::vector<Texture>);
            ~Material();
        };
        
        class MaterialUse {
        public:
            MaterialUse(const Material&);
            ~MaterialUse();
        };
    }
}

#endif /* defined(__OpenGLFramework__material__) */