//
//  ray3.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 21.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef OpenGLFramework_ray3_h
#define OpenGLFramework_ray3_h

#include "../vec3.h"

namespace lkogl {
    namespace math {
        namespace elements {
            
            template<typename T>
            struct Ray3 {
                Vec3<T> origin;
                Vec3<T> direction;
                
                Ray3(const Vec3<T>& orig, const Vec3<T>& dir) : origin(orig), direction(dir) {}
                
                ~Ray3() {}
                
                void at(T t)
                {
                    return origin + t*direction;
                }
            };
        }
    }
}

#endif
