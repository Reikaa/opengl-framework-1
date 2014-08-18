//
//  image_height_map.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 17.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "image_height_map.h"
#include <map>

namespace lkogl {
    namespace resources {
        namespace mesh_loader {
            ImageHeightMap::ImageHeightMap(int width, int height) : points_(new float[width*height]), width_(width), height_(height)
            {}
            
            ImageHeightMap::~ImageHeightMap()
            {
                free(points_);
            }
                
            void ImageHeightMap::setHeightAt(int x, int y, float h)
            {
                points_[y + width_*x] = h;
            }
                
            IndexModel ImageHeightMap::toIndexedModel() const
            {
                IndexModel result;
                int vertexCount = width_*height_;
                int triangleCount = 0;
                std::multimap<unsigned int, math::Vec3<float>> normalMap;
                float scale = 1;
                
                for(int x=0;x<width_;x++) {
                    for(int y=0;y<height_;y++) {
                        float vx = (x-width_/2)*scale;
                        float vy = (points_[y + width_*x])*scale;
                        float vz = (y-height_/2)*scale;
                        float tu = 0;
                        float tv = 0;
                        result.positions_.push_back(math::Vec3<float>(vx,vy,vz));
                        result.texCoords_.push_back({tu,tv});
                    }
                }
                
                for(int i=1;i<=vertexCount-height_;i++) {
                    if((i)%height_ == 0) {
                        continue;
                    }
                    result.indices_.push_back(i-1+height_);
                    result.indices_.push_back(i-1);
                    result.indices_.push_back(i+height_);
                    
                    result.indices_.push_back(i-1);
                    result.indices_.push_back(i);
                    result.indices_.push_back(i+height_);
                    
                    triangleCount+=2;
                }
                
                for(int i=0;i<triangleCount*3;i+=3) {
                    math::Vec3<float> v1p = result.positions_[result.indices_[i]];
                    math::Vec3<float> v2p = result.positions_[result.indices_[i+1]];
                    math::Vec3<float> v3p = result.positions_[result.indices_[i+2]];
                    
                    math::Vec3<float> sideA = v1p-v2p;
                    math::Vec3<float> sideB = v2p-v3p;
                    
                    math::Vec3<float> faceNormal = math::normalize(math::cross(sideA,sideB));
                    
                    normalMap.insert(std::make_pair(result.indices_[i], faceNormal));
                    normalMap.insert(std::make_pair(result.indices_[i+1], faceNormal));
                    normalMap.insert(std::make_pair(result.indices_[i+2], faceNormal));
                }
                
                for(int i=0;i<vertexCount;i++) {
                    auto lb = normalMap.lower_bound(i);
                    auto ub = normalMap.upper_bound(i);
                    math::Vec3<float> avgNormal;
                    int normalCount = 0;
                    
                    for(auto i=lb;i!=ub;i++) {
                        avgNormal += i->second;
                        normalCount++;
                    }
                    if(normalCount>0)
                        avgNormal /= normalCount;
                    
                    result.normals_.push_back(avgNormal);
                }
                
                
                return result;
            }
            
            ImageHeightMap heigh_map_from_image(const utils::Image& img, unsigned short filterRadius)
            {
                unsigned short filterLength = 2*filterRadius + 1;
                unsigned short filterPxCount = filterLength*filterLength;
                
                int width = img.width();
                int height = img.height();
                
                int resWidth = width - filterRadius*2;
                int resHeight = height - filterRadius*2;
                
                Uint32 * pixels = (Uint32 *)img.pixels();
                ImageHeightMap result(resWidth, resHeight);
                
                for(int x=0;x<resWidth;x++) {
                    for(int y=0;y<resWidth;y++) {
                        float heightSum = 0;
                        for(short fx=0;fx<filterLength;fx++) {
                            for(short fy=0;fy<filterLength;fy++) {
                                Uint32 p = pixels[ ( (y+fy) * width ) + x+fx ];
                                float h = (p&0xff);
                                
                                heightSum += h;
                            }
                        }
                        result.setHeightAt(x, y, (heightSum/filterPxCount)-0x88);
                    }
                }
                
                return result;
            }
        }
    }
}
