//
//  material.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__material__
#define __OpenGLFramework__material__

#include "texture.h"
#include "shader.h"

namespace lkogl {
    namespace graphics {
        class Material {
            Texture texture_;
            float specularIntensity_ = 4;
            float specularPower_ = 4;
        public:
            Material(const Material& mat);
            Material(Texture, float specInt, float specPow);
            ~Material();
            
            friend class MaterialUse;
        };
        
        class MaterialUse {
            TextureUse _texUse;
        public:
            MaterialUse(const ProgramUse& p, const Material&);
            ~MaterialUse();
        };
    }
}

#endif /* defined(__OpenGLFramework__material__) */