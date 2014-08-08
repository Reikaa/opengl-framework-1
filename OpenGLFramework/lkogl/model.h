//
//  model.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 08.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__model__
#define __OpenGLFramework__model__

#include <stdio.h>
#include "shader.h"
#include "material.h"

namespace lkogl {
    namespace graphics {
        class Model {
            const GeometryObject& geometry_;
            const Material& material_;
        public:
            Model(const GeometryObject& geo, const Material& mat);
            ~Model();
        };
    }
}

#endif /* defined(__OpenGLFramework__model__) */
