//
//  sphere3.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 21.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef OpenGLFramework_sphere3_h
#define OpenGLFramework_sphere3_h

#include "../vec3.h"

namespace lkogl {
    namespace math {
        namespace geo {
            
            template<typename T>
            struct Sphere3 {
                Vec3<T> center;
                T radius;
                
                Sphere3(const T& r) : radius(r) {}
                
                Sphere3(const Vec3<T>& c, T r) : radius(r), center(c) {}
                
                ~Sphere3() {}
                
                T surface() const
                {
                    return M_PI_4/3 * radius * radius * radius;
                }
                
                T volume() const
                {
                    return M_PI_4 * radius * radius;
                }
            };
            
        }
    }
}


#endif
