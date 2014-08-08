//
//  material.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__material__
#define __OpenGLFramework__material__

#include <stdio.h>
#include <vector>

#include "texture.h"
#include "shader.h"

namespace lkogl {
    namespace graphics {
        class Material {
        public:
            Material(const Program&, const std::vector<Texture>&);
            ~Material();
        };
        
        class MaterialUse {
            MaterialUse(const Material&);
            ~MaterialUse();
        };
    }
}

#endif /* defined(__OpenGLFramework__material__) */