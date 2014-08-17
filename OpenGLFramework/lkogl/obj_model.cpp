//
//  obj_model.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 12.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "obj_model.h"

#include <unordered_map>
#include <fstream>
#include <sstream>

#include "file_path.h"

namespace lkogl {
    namespace resources {
        namespace mesh_loader {

            IndexModel OBJModel::toIndexedModel() const {
                IndexModel result;
                typedef std::unordered_map<OBJIndex, unsigned int> mapType;
                mapType indexMap;
                unsigned int numIndex = 0;
                
                for(const OBJIndex currentIndex : indices_) {
                    math::Vec4<float> pos = positions_.at(currentIndex.vertexIndex);
                    math::Vec3<float> texCoord;
                    math::Vec3<float> normal;
                    if(hasTexCoords_) {
                        texCoord = texCoords_.at(currentIndex.texCoordIndex);
                    }
                    if(hasNormals_) {
                        normal = normals_.at(currentIndex.normalIndex);
                    }

                    const std::pair<mapType::iterator, bool> p = indexMap.insert(std::make_pair(currentIndex, numIndex));
                    
                    if(p.second) {
                        result.positions_.push_back({pos.x, pos.y, pos.z});
                        result.texCoords_.push_back({texCoord.x, texCoord.y});
                        result.normals_.push_back(normal);
                        numIndex++;
                    }
                    
                    result.indices_.push_back(p.first->second);
                }
                
                return result;
            };
            
            OBJModel obj_from_file(const std::string& filename) {
                OBJModel model;
                bool hasTexCoords = false;
                bool hasNormals = false;
                
                std::ifstream infile(utils::Path().relative(filename));
                std::string line;
                float fa, fb, fc, fd;
                int lineNumber = 0;
                
                while (std::getline(infile, line))
                {
                    lineNumber++;
                    std::istringstream iss(line);
                    char firstChar;
                    
                    if(iss >> firstChar) {
                        switch (firstChar) {
                            case '#' : {
                                continue;
                            }
                            case 'o' : {
                                continue;
                            }
                            case 's' : {
                                continue;
                            }
                            case 'v': {
                                char secondChar;
                                if(iss >> secondChar) {
                                    switch (secondChar) {
                                        case 'n':
                                            if(iss >> fa >> fb >> fc) {
                                                model.normals_.push_back({fa, fb, fc});
                                            } else {
                                                throw "exptected 3 normal coords";
                                            }
                                            break;
                                        case 't':
                                            if(iss >> fa >> fb) {
                                                if(!(iss >> fc)) {
                                                    fc = 0.0;
                                                }
                                                model.texCoords_.push_back({fa, fb, fc});
                                            } else {
                                                throw "exptected 2 texture coords";
                                            }
                                            break;
                                        default:
                                            iss.putback(secondChar);
                                            if(iss >> fa >> fb >> fc) {
                                                if(!(iss >> fd)) {
                                                    fd = 1.0;
                                                }
                                                model.positions_.push_back({fa, fb, fc, fd});
                                            } else {
                                                throw "exptected 3 vertex coords";
                                            }
                                    }
                                }
                                break;
                            };
                            case 'f': {
                                std::string token;
                                std::vector<OBJIndex> polygonVertices;
                                polygonVertices.reserve(3);
                                
                                while(iss >> token) {
                                    OBJIndex objI;
                                    size_t start = 0;
                                    unsigned int n = 0;
                                    do {
                                        int index = 0;
                                        std::stringstream(token.substr(start)) >> index;

                                        switch(n++) {
                                            case 0:
                                                objI.vertexIndex = index - 1;
                                                break;
                                            case 1:
                                                objI.texCoordIndex = index - 1;
                                                if(index > 0) {
                                                    hasTexCoords = true;
                                                }
                                                break;
                                            case 2:
                                                objI.normalIndex = index - 1;
                                                if(index > 0) {
                                                    hasNormals = true;
                                                }
                                                break;
                                            default:
                                                throw "too many indices, max 3 allowed";
                                        }
                                    } while((start = token.find('/', start)) != std::string::npos && ++start);

                                    polygonVertices.push_back(objI);
                                }

                                
                                if(polygonVertices.size() < 3) {
                                    throw "faces must have at least 3 vertices";
                                }
                                
                                for(size_t i=0,j=polygonVertices.size()-2;i<j; i++) {
                                    model.indices_.push_back(polygonVertices.at(0));
                                    model.indices_.push_back(polygonVertices.at(1+i));
                                    model.indices_.push_back(polygonVertices.at(2+i));
                                }
                                
                                break;
                            };
                            default: {
                                iss.putback(firstChar);
                                std::string def;
                                iss >> def;
                                if(def == "mtllib") {
                                    
                                } else if(def == "usemtl") {
                                    
                                } else {
                                    throw "unexpected definition";
                                }
                            }
                        }
                    }
                    
                }

                model.hasNormals_ = hasNormals;
                model.hasTexCoords_ = hasTexCoords;
                
                return model;
            }
        }
    }
}