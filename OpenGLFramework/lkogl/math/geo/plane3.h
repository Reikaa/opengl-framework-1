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
        namespace geo {
        
            template <typename T>
            struct Plane3
            {
                Vec3<T> normal;
                T constant;
                
                Plane3() {}
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
                Vec3<T> crossBC = b.normal.cross(c.normal);
                
                T f = -dot(a.normal, crossBC);

                T v1 = crossBC.scaled(a.constant);
                T v2 = c.normal.cross(a.normal).scaled(b.constant);
                T v3 = a.normal.cross(b.normal).scaled(c.constant);
                
                return (v1 + v2 + v3) / f;
            }
        }
    }
}

#endif /* defined(__OpenGLFramework__plane3__) */
