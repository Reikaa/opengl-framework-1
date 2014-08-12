//
//  index_model.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 12.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__index_model__
#define __OpenGLFramework__index_model__

#include <vector>
#include "math.h"
#include "mesh.h"

namespace lkogl {
    namespace resources {
        namespace mesh_loader {
            class IndexModel {
            public:
                std::vector<math::Vec3<float>> positions_;
                std::vector<math::Vec2<float>> texCoords_;
                std::vector<math::Vec3<float>> normals_;
                std::vector<unsigned int> indices_;
                
                geometry::Mesh toMesh() const;
            };
        }
    }
}



#endif /* defined(__OpenGLFramework__index_model__) */
