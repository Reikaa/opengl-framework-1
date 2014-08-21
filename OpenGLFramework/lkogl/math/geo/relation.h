//
//  relation.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 21.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__relation__
#define __OpenGLFramework__relation__

#include "../vec3.h"
#include "./plane3.h"
#include "./frustum3.h"
#include "./sphere3.h"
#include "./aabb3.h"

namespace lkogl {
    namespace math {
        namespace geo {
            enum class VolumeRelation {
                INSIDE,
                OUTSIDE,
                INTERSECTING
            };
            
            template<typename T>
            VolumeRelation relationship(const Frustum3<T>& frus, const Aabb3<T>& aabb)
            {
                int inCount = 0;
                int outCount = 0;

                for(Vec3<T> c : aabb.corners()) {
                    if(frus.contains(c)) {
                        inCount++;
                    } else {
                        outCount++;
                    }
                }
                
                if(!inCount) {
                    return VolumeRelation::OUTSIDE;
                } else if(!outCount) {
                    return VolumeRelation::INTERSECTING;
                } else {
                    return VolumeRelation::INSIDE;
                }
            }
            
            template<typename T>
            VolumeRelation relationship(const Frustum3<T>& frus, const Sphere3<T>& sphere)
            {
                VolumeRelation result = VolumeRelation::INSIDE;
                std::array<Plane3<T>, 6> planes = frus.faces();

                
                for(int i = 0; i < 6; i++) {
                    T distance = distance(planes[i], sphere.center);
                    
                    if (distance < -sphere.radius) {
                        return VolumeRelation::OUTSIDE;
                    }
                    else if (distance < sphere.radius) {
                        result =  VolumeRelation::INTERSECTING;
                    }
                }
                
                return result;
            }
            
            template<typename T>
            VolumeRelation relationship(const Frustum3<T>& frus, const Vec3<T>& point)
            {
                return contains(frus, point) ? VolumeRelation::INSIDE : VolumeRelation::OUTSIDE;
            }
            
            //
            // AABB3 contains
            //
            
            template<typename T>
            bool contains(const Aabb3<T>& outer, const Aabb3<T>& inner) {
                for(Vec3<T> c : inner.corners()) {
                    if(!contains(outer, c)) {
                        return false;
                    }
                }
                
                return true;
            }
            
            template<typename T>
            bool contains(const Aabb3<T>& aabb, const Vec3<T>& p) {
                return (aabb.min << p) && (aabb.max >> p);
            }
            
            template<typename T>
            bool contains(const Aabb3<T>& a, const Sphere3<T>& b) {
                return (a.min << (b.center - b.radius))
                    && (a.max >> (b.center + b.radius));
            }
            
            //
            // Sphere3 contains
            //
            template<typename T>
            bool contains(const Sphere3<T>& outer, const Sphere3<T>& inner) {
                return (outer.radius-inner.radius) > (outer.center-inner.center).length();
            }
            
            template<typename T>
            bool contains(const Sphere3<T>& sphere, const Vec3<T>& p) {
                return sphere.radius > (sphere.center-p).length();
            }
            
            template<typename T>
            bool contains(const Sphere3<T>& outer, const Aabb3<T>& inner) {
                for(Vec3<T> c : inner.corners()) {
                    if(!contains(outer, c)) {
                        return false;
                    }
                }
                
                return true;
            }
            
            //
            // Frustum contains
            //
            template<typename T>
            bool contains(const Frustum3<T>& frus, const Sphere3<T>& sphere) {
                std::array<Plane3<T>, 6> planes = frus.faces();

                
                for(int i = 0; i < 6; i++) {
                    T distance = distance(planes[i], sphere.center);
                    
                    if (distance < -sphere.radius || distance < sphere.radius) {
                        return false;
                    }
                }
                
                return true;
            }
            
            template<typename T>
            bool contains(const Frustum3<T>& frus, const Vec3<T>& point)
            {
                std::array<Plane3<T>, 6> planes = frus.faces();
                for(int i = 0; i < 6; ++i) {
                    if(distance(planes[i], point) < 0.0) {
                        return false;
                    }
                }
                
                return true;
            }
            
            template<typename T>
            bool contains(const Frustum3<T>& frus, const Aabb3<T>& aabb) {
                for(Vec3<T> c : aabb.corners()) {
                    if(!frus.contains(c)) {
                        return false;
                    }
                }
                
                return true;
            }
            
            // Distance
            
            template<typename T>
            T distance(const Plane3<T>& a, const Vec3<T>& b) {
                return dot(a.normal, b) + a.constant;
            }
        }
    }
}

#endif /* defined(__OpenGLFramework__relation__) */
