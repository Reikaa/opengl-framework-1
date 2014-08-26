//
//  material.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__material__
#define __OpenGLFramework__material__

#include "./texture.h"
#include "./shader/shader.h"

namespace lkogl {
    namespace graphics {
        class Material {
            Texture texture_;
            Texture normalMap_;
            float specularIntensity_ = 4;
            float specularPower_ = 4;
        public:
            Material(const Material& mat);
            Material(Texture, Texture, float specInt, float specPow);
            ~Material();
            
            friend class MaterialUse;
        };
        
        class MaterialUse {
            TextureUse texUse_;
            TextureUse texNormalUse_;
        public:
            MaterialUse(const shader::ProgramUse& p, const Material&);
            ~MaterialUse();
        };
    }
}

#endif /* defined(__OpenGLFramework__material__) */