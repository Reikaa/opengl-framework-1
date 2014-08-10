//
//  math.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__math__
#define __OpenGLFramework__math__

#include <math.h>
#include <string>


#include "vec3.h"
#include "vec2.h"
#include "vec4.h"
#include "mat4.h"
#include "quat.h"

namespace lkogl {
    namespace math {
        typedef float basetype;
        
        template<typename T>
        Mat4<T> perspective(T const & fovy, T const & aspect, T const & zNear, T const & zFar)
        {
            T tanHalfFovy = tan(fovy / static_cast<T>(2));
            
            Mat4<T> result(static_cast<T>(0));
            result[0][0] = static_cast<T>(1) / (aspect * tanHalfFovy);
            result[1][1] = static_cast<T>(1) / (tanHalfFovy);
            result[2][2] = - (zFar + zNear) / (zFar - zNear);
            result[2][3] = - static_cast<T>(1);
            result[3][2] = - (static_cast<T>(2) * zFar * zNear) / (zFar - zNear);
            return result;
        }
        
        template<typename T>
        T radians(const T& deg) {
            return deg * 2 * M_PI / 360.f;
        }
    }
}

#endif /* defined(__OpenGLFramework__math__) */
