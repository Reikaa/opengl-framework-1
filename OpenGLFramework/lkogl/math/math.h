//
//  math.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__math__
#define __OpenGLFramework__math__

#include <string>

#include "./base.h"
#include "./vec3.h"
#include "./vec2.h"
#include "./vec4.h"
#include "./mat4.h"
#include "./quat.h"


#include "./geo/frustum3.h"
#include "./geo/plane3.h"
#include "./geo/sphere3.h"
#include "./geo/aabb3.h"
#include "./geo/relation.h"

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
        Mat4<T> ortho
        (
         T const & left,
         T const & right,
         T const & bottom,
         T const & top
         )
        {
            Mat4<T> result(1);
            result[0][0] = static_cast<T>(2) / (right - left);
            result[1][1] = static_cast<T>(2) / (top - bottom);
            result[2][2] = - static_cast<T>(1);
            result[3][0] = - (right + left) / (right - left);
            result[3][1] = - (top + bottom) / (top - bottom);
            
            return result;
        }
        
        
        
        template <typename T>
        std::string toString(const Vec3<T>& v)
        {
            std::string result;
            result += "(" + std::to_string(v.x) + ", ";
            result += std::to_string(v.y) + ", ";
            result += std::to_string(v.z) + ")";
            
            return result;
        }
        
        
        template <typename T>
        std::string toString(const Vec2<T>& v)
        {
            std::string result;
            result += "(" + std::to_string(v.x) + ", ";
            result += std::to_string(v.y) + ")";
            
            return result;
        }
        
        
        
        template <typename T>
        std::string toString(const Vec4<T>& v)
        {
            std::string result;
            result += "(" + std::to_string(v.x) + ", ";
            result += std::to_string(v.y) + ", ";
            result += std::to_string(v.z) + ", ";
            result += std::to_string(v.w) + ")";
            
            return result;
        }
        
        
        
        template <typename T>
        std::string toString(const Mat4<T>& m)
        {
            std::string result = "---\n";
            result += toString(m[0]) + "\n";
            result += toString(m[1]) + "\n";
            result += toString(m[2]) + "\n";
            result += toString(m[3]);
            
            return result;
        }
        
        
        
        
        template <typename T>
        std::string toString(const Quat<T>& v)
        {
            std::string result;
            result += "(" + std::to_string(v.x) + ", ";
            result += std::to_string(v.y) + ", ";
            result += std::to_string(v.z) + ", ";
            result += std::to_string(v.w) + ")";
            
            return result;
        }
    }
}

#endif /* defined(__OpenGLFramework__math__) */
