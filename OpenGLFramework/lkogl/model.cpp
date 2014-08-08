//
//  model.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 08.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "model.h"
#include <iostream>

namespace lkogl {
    namespace graphics {
        Model::Model(GeometryObject geo, Material mat) :
        geometry_(std::move(geo)), material_(std::move(mat))
        {
        }
        
        Model::~Model()
        {
        }
        
        Model::Model(Model&& m) :geometry_(std::move(m.geometry_)), material_(std::move(m.material_)) {
        }
        
        const GeometryObject& Model::geometry() const
        {
            return geometry_;
        }
        
        const Material& Model::material() const
        {
            return material_;
        }
    }
}