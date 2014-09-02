//
//  plane3.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 21.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__plane3__
#define __OpenGLFramework__plane3__

#include "../vec3.h"

namespace lkogl {
    namespace math {
        namespace elements {
        
            template <typename T>
            struct Plane3
            {
                Vec3<T> normal;
                T constant;
                
                Plane3() : normal({0,1,0}), constant(0) {}
                
                Plane3(const Vec3<T>& n, const Vec3<T>& p) : normal(n), constant(dot(n,p)) {
                    normalize();
                }
                
                Plane3(const Vec3<T>& n, const T& c) : normal(n), constant(c) {
                    normalize();
                }
                
                explicit Plane3(const Vec3<T>& n) : normal(math::normalize(n)), constant(0) {}
                
                ~Plane3() {}
                
                void setNormalConstant(const Vec3<T>& n, const T& c) {
                    normal = n;
                    constant = c;
                }
                
                void normalize() {
                    T inverseLength = 1.0 / length(normal);
                    normal *= inverseLength;
                    constant *= inverseLength;
                }
            };
            
            template<typename T>
            Vec3<T> intersection(const Plane3<T>& a, const Plane3<T>& b, const Plane3<T>& c)
            {
                Vec3<T> crossBC = cross(b.normal, c.normal);
                
                T f = dot(a.normal, crossBC);

                Vec3<T> v1 = crossBC * a.constant;
                Vec3<T> v2 = cross(c.normal, a.normal) * b.constant;
                Vec3<T> v3 = cross(a.normal, b.normal) * c.constant;
                
                return (v1 + v2 + v3) / f;
            }
        }
    }
}

#endif /* defined(__OpenGLFramework__plane3__) */
