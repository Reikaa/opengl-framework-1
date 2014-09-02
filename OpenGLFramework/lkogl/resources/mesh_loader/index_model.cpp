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
                                                        {},
                                                        texCoords_.at(currentIndex)
                    });
                    if(++indexNum%3 == 0) {
                        triangles.push_back(geometry::Triangle{
                            indexNum-3,
                            indexNum-2,
                            indexNum-1,
                        });
                        
                        calculateTangent(vertices[indexNum-3], vertices[indexNum-2], vertices[indexNum-1]);
                    }
                }
                
                return geometry::Mesh(vertices, triangles);
            }
            
            math::elements::Aabb3<float> IndexModel::bounding() const
            {
                math::Vec3<float> min;
                math::Vec3<float> max;
                
                for(const unsigned int currentIndex : indices_) {
                    math::Vec3<float> p = positions_.at(currentIndex);
                    
                    min = math::min<float>(p, min);
                    max = math::max<float>(p, max);
                }
                
                return math::elements::Aabb3<float>(min, max);
            }
            
            void calculateTangent(geometry::Vertex& v1, geometry::Vertex& v2, geometry::Vertex& v3)
            {
                math::Vec3<float> tangent(1,0,0);
                math::Vec3<float> tangent2(1,0,0);

                math::Vec3<float> Q1 = v2.position - v1.position;
                math::Vec3<float> Q2 = v3.position - v1.position;
                
                math::Vec2<float> D1 = v2.textureCoord - v1.textureCoord;
                math::Vec2<float> D2 = v3.textureCoord - v1.textureCoord;
                
                float det = D1.x * D2.y - D2.x * D1.y;
                
                if(det != 0) {
                    tangent = (Q1 * D2.y - Q2 * D1.y) * (1.0f/det);
                    tangent2 = (Q2 * D1.x - Q1 * D2.x) * (1.0f/det);
                }
                
                float nDotT1 = math::dot(v1.normal, tangent);
                float nDotT2 = math::dot(v2.normal, tangent);
                float nDotT3 = math::dot(v3.normal, tangent);
                
                math::Vec3<float> t1 = math::normalize(tangent - nDotT1 * v1.normal);
                math::Vec3<float> t2 = math::normalize(tangent - nDotT2 * v2.normal);
                math::Vec3<float> t3 = math::normalize(tangent - nDotT3 * v3.normal);
                
                float h1 = (math::dot(math::cross(v1.normal, t1), tangent2) < 0.0f) ? -1.0f : 1.0f;
                float h2 = (math::dot(math::cross(v2.normal, t2), tangent2) < 0.0f) ? -1.0f : 1.0f;
                float h3 = (math::dot(math::cross(v3.normal, t3), tangent2) < 0.0f) ? -1.0f : 1.0f;
                
                v1.tangent = h1*math::Vec4<float>(t1, 1);
                v2.tangent = h2*math::Vec4<float>(t2, 1);
                v3.tangent = h3*math::Vec4<float>(t3, 1);
            }
        }
    }
}