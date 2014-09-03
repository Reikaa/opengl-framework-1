//
//  aabb3.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 21.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef OpenGLFramework_aabb3_h
#define OpenGLFramework_aabb3_h

#include "../vec3.h"
#include "../mat4.h"
#include "./plane3.h"

namespace lkogl {
    namespace math {
        namespace elements {
            
            template<typename T>
            struct Aabb3 {
                Vec3<T> min;
                Vec3<T> max;

                Aabb3() {}
                
                Aabb3(const T& side) : Aabb3(side, side, side) {}

                Aabb3(const T& w, const T& h, const T& d) :
                    min(-w/2, -h/2, -d/2),
                    max(w/2, h/2, d/2)
                {}
                
                Aabb3(const Vec3<T>& minp, const Vec3<T>& maxp) :min(minp), max(maxp) {}
                ~Aabb3() {}
                
                std::array<Vec3<T>, 8> corners() const
                {
                    
                    return {
                        min,
                        Vec3<T>{max.x,min.y,min.z},
                        Vec3<T>{max.x,max.y,min.z},
                        Vec3<T>{min.x,max.y,min.z},
                        Vec3<T>{min.x,max.y,max.z},
                        Vec3<T>{min.x,min.y,max.z},
                        Vec3<T>{max.x,min.y,max.z},
                        max
                    };
                }
                
                std::array<Plane3<T>, 6> faces() const {
                    Vec3<T> x(max.x-min.x,0,0);
                    Vec3<T> y(0,max.y-min.y,0);
                    Vec3<T> z(0,0,max.z-min.z);
                    
                    return {
                        Plane3<T>(cross(y,z), min),
                        Plane3<T>(-cross(z,z), max),
                        Plane3<T>(cross(x,z), max),
                        Plane3<T>(-cross(x,z), min),
                        Plane3<T>(cross(x,y), min),
                        Plane3<T>(-cross(x,y), max)
                    };
                    
                    return faces;
                }
                
                Vec3<T> center() const
                {
                    return (min+max)/((T)2);
                }
                
                T surface() const
                {
                    Vec3<T> diagonal = max - min;
                    return 2 * (diagonal.x*diagonal.y + diagonal.x*diagonal.z + diagonal.y*diagonal.z);
                }
                
                T volume() const
                {
                    Vec3<T> diagonal = max - min;
                    return diagonal.x * diagonal.y * diagonal.z;
                }
                
                Vec3<T> dimensions() const
                {
                    return max - min;
                }
            };
            
            template <typename T>
            Aabb3<T> transformed(const Aabb3<T>& box, const Mat4<T>& m)
            {
                math::Vec3<T> center = (box.min + box.max)/2.0f;
                math::Vec3<T> halfExtents = (box.max - box.min)/2.0f;
                
                math::Vec3<T> newCenter = math::vec3_cast<T>(m * center);
                math::Vec3<T> newHalfEx = math::vec3_cast<T>(m * math::Vec4<float>(halfExtents, 0));
                
                std::array<Vec3<T>, 8> corners = box.corners();
                math::Vec3<T> min;
                math::Vec3<T> max;
                int i=0;
                for(auto c : corners) {
                    math::Vec3<T> newC = math::vec3_cast<T>(m * c);
                    
                    if(i++==0) {
                        min = newC;
                        max = newC;
                    } else {
                        min = math::min(min, newC);
                        max = math::max(max, newC);
                    }
                }
                
                return Aabb3<T>(min, max);
            }
        }
    }
}

#endif
