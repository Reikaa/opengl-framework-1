//
//  math.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__math__
#define __OpenGLFramework__math__

#include <stdio.h>

namespace lkogl {
    namespace math {
        typedef float basetype;
        
        template <typename T = basetype>
        struct Vec3 {
            T x, y, z;
            Vec3();
            Vec3(const T& x, const T& y, const T& z);
            ~Vec3();
        };
        
        template <typename T = basetype>
        struct Vec4 {
            T x, y, z, w;
            Vec4();
            Vec4(const T& x, const T& y, const T& z, const T& w);
            ~Vec4();
        };
        
        template <typename T = basetype>
        struct Mat4 {
            Mat4();
            ~Mat4();
        };
        
        template <typename T = basetype>
        struct Quat {
            T x, y, z, w;
            Quat();
            Quat(const T& angle, const Vec3<T>& axis);
            Quat(const T& x, const T& y, const T& z, const T& w);
            ~Quat();
        };
        
        template<typename T = basetype>
        Quat<T> rotation(const T& angle, const Vec3<T>& axis);
        
        template<typename T = basetype>
        Quat<T> rotation(const Vec3<T>& v1, const Vec3<T>& v2);
    }
}

#endif /* defined(__OpenGLFramework__math__) */
