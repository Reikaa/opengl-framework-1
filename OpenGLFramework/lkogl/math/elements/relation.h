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
        namespace elements {
            enum class VolumeRelation {
                INSIDE,
                OUTSIDE,
                INTERSECTING
            };
            
            template<typename T>
            VolumeRelation relationship(const Frustum3<T>& frus, const Aabb3<T>& aabb)
            {
                int totalIn = 0;
                
                for(Plane3<T> pl : frus.faces()) {
                    int inCount = 8;
                    int ptIn = 1;
                    
                    for(auto c : aabb.corners()) {
                        
                        // test this point against the planes
                        if(distance(pl, c) > 0) {
                            ptIn = 0;
                            --inCount;
                        }
                    }
                    
                    // were all the points outside of plane p?
                    if(inCount == 0)
                        return VolumeRelation::OUTSIDE;
                    
                    // check if they were all on the right side of the plane
                    totalIn += ptIn;
                }
                
                if(totalIn == 6) {
                    return VolumeRelation::INSIDE;
                }
                
                return VolumeRelation::INTERSECTING;
            }
            
            template<typename T>
            VolumeRelation relationship(const Frustum3<T>& frus, const Sphere3<T>& sphere)
            {
                VolumeRelation result = VolumeRelation::INSIDE;
                std::array<Plane3<T>, 6> planes = frus.faces();
                
                for(int i = 0; i < 6; i++) {
                    T d = distance(planes[i], sphere.center);
                    
                    if (d > sphere.radius) {
                        return VolumeRelation::OUTSIDE;
                    }
                    else if (d > -sphere.radius) {
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
            
            template<typename T>
            VolumeRelation relationship(const Aabb3<T>& a, const Aabb3<T>& b)
            {
                if(intersects(a,b)) {
                    if(contains(a,b)) {
                        return VolumeRelation::INSIDE;
                    } else {
                        return VolumeRelation::INTERSECTING;
                    }
                } else {
                    return VolumeRelation::OUTSIDE;
                }
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
            // Aabb3 intersects
            //
            
            template<typename T>
            bool intersects(const Aabb3<T>& a, const Aabb3<T>& b) {
                return (a.min.x < b.max.x) && (a.min.y < b.max.y) && (a.min.z < b.max.z) && (a.max.x > b.min.x) && (a.max.y > b.min.y) && (a.max.z > b.min.z);
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
                    T d = distance(planes[i], point);
                    if(d > 0.0) {
                        return false;
                    }
                }
                
                return true;
            }
            
            template<typename T>
            bool contains(const Frustum3<T>& frus, const Aabb3<T>& aabb) {
                for(Vec3<T> c : aabb.corners()) {
                    if(!contains(frus, c)) {
                        return false;
                    }
                }
                
                return true;
            }
            
            // Distance
            
            template<typename T>
            T distance(const Plane3<T>& a, const Vec3<T>& b) {
                return dot(a.normal, b) - a.constant;
            }
        }
    }
}

#endif /* defined(__OpenGLFramework__relation__) */
