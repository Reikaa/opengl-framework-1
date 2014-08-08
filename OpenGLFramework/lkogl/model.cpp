//
//  model.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 08.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "model.h"

namespace lkogl {
    namespace graphics {
        Model::Model(const GeometryObject& geo, const Material& mat) :
        geometry_(geo), material_(mat)
        {
            
        }
        
        Model::~Model()
        {
        
        }
    }
}