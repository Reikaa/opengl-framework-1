//
//  obj_model.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 12.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__obj_model__
#define __OpenGLFramework__obj_model__

#include <string>
#include <vector>

#include "../../math/math.h"
#include "./index_model.h"

namespace lkogl {
    namespace resources {
        namespace mesh_loader {
            struct OBJIndex {
                unsigned int vertexIndex;
                unsigned int texCoordIndex;
                unsigned int normalIndex;
                
                bool operator==(const OBJIndex &other) const
                { return (vertexIndex == other.vertexIndex
                          && texCoordIndex == other.texCoordIndex
                          && normalIndex == other.normalIndex);
                }
            };
            
            class OBJModel {
            public:
                class Exception {
                public:
                    Exception(const std::string& msg) {}
                    Exception() {}
                };
                std::vector<math::Vec4<float>> positions_;
                std::vector<math::Vec3<float>> texCoords_;
                std::vector<math::Vec3<float>> normals_;
                std::vector<OBJIndex> indices_;
                
                bool hasTexCoords_;
                bool hasNormals_;
                
                IndexModel toIndexedModel() const;
            };
            
            
            OBJModel obj_from_file(const std::string& filename);
        }
    }
}

namespace std {
    
    template <>
    struct hash<lkogl::resources::mesh_loader::OBJIndex>
    {
        std::size_t operator()(const lkogl::resources::mesh_loader::OBJIndex& k) const
        {
            constexpr int BASE = 7;
            constexpr int MULTIPL = 13;
            
            int hash = BASE;
            hash = MULTIPL * hash + k.vertexIndex;
            hash = MULTIPL * hash + k.texCoordIndex;
            hash = MULTIPL * hash + k.normalIndex;
            
            return hash;
        }
    };
    
    
}

#endif /* defined(__OpenGLFramework__obj_model__) */
