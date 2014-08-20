//
//  index_model.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 12.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./index_model.h"

namespace lkogl {
    namespace resources {
        namespace mesh_loader {
            geometry::Mesh IndexModel::toMesh() const {
                std::vector<geometry::Vertex> vertices;
                std::vector<geometry::Triangle> triangles;
                unsigned int indexNum = 0;
                
                for(const unsigned int currentIndex : indices_) {
                    vertices.push_back(geometry::Vertex{
                                                        positions_.at(currentIndex),
                                                        normals_.at(currentIndex),
                                                        texCoords_.at(currentIndex)
                    });
                    if(++indexNum%3 == 0) {
                        triangles.push_back(geometry::Triangle{
                            indexNum-3,
                            indexNum-2,
                            indexNum-1,
                        });
                    }
                }
                
                return geometry::Mesh(vertices, triangles);
            }
        }
    }
}