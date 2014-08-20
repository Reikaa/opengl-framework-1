//
//  base_light.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./base_light.h"

namespace lkogl {
    namespace graphics {
        namespace lighting {
            
            BaseLight::BaseLight(math::Vec3<float> color, float intensity) : color_(color), intensity_(intensity)
            {}
            
            BaseLight::~BaseLight()
            {}
            
        }
    }
}