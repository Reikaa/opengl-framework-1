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

namespace lkogl {
    namespace math {
        namespace geo {
            
            template<typename T>
            struct Aabb3 {
                Vec3<T> min;
                Vec3<T> max;

                Aabb3() {}
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
            };
            
            template <typename T>
            Aabb3<T> transformed(const Aabb3<T>& box, const Mat4<T>& m)
            {
                math::Vec3<T> center = (box.min + box.max)/2.0f;
                math::Vec3<T> halfExtents = (box.max - box.min)/2.0f;
                
                math::Vec4<T> newCenter = m * math::Vec4<float>(center.x, center.y, center.z, 1);
                math::Vec4<T> newHalfEx = m * math::Vec4<float>(halfExtents.x, halfExtents.y, halfExtents.z, 0);
                
                return Aabb3<T>({
                    newCenter.x-math::max(newHalfEx.x, halfExtents.x),
                    newCenter.y-math::max(newHalfEx.y, halfExtents.y),
                    newCenter.z-math::max(newHalfEx.z, halfExtents.z),
                },{
                    newCenter.x+math::max(newHalfEx.x, halfExtents.x),
                    newCenter.y+math::max(newHalfEx.y, halfExtents.y),
                    newCenter.z+math::max(newHalfEx.z, halfExtents.z),
                });
            }
        }
    }
}

#endif
