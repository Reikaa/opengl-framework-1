//
//  model.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 08.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__model__
#define __OpenGLFramework__model__

#include "geometry_object.h"
#include "material.h"

namespace lkogl {
    namespace graphics {
        class Model {
            GeometryObject geometry_;
            Material material_;
        public:
            Model(const GeometryObject geo, Material mat);
            Model(Model&& m);

            ~Model();
            
            const GeometryObject& geometry() const;
            const Material& material() const;
        };
    }
}

#endif /* defined(__OpenGLFramework__model__) */
