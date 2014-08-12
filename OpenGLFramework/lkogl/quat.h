//
//  quat.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 08.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__quat__
#define __OpenGLFramework__quat__

#include "vec3.h"
#include "vec4.h"

namespace lkogl {
    namespace math {
        typedef float basetype;
        
        template <typename T = basetype>
        struct Quat {
            T x, y, z, w;
            Quat() : x(0) , y(0) , z(0) , w(1)
            {
            }
            
            Quat(const Quat<T>& o) : x(o.x), y(o.y), z(o.z), w(o.w)
            {
            }
            
            Quat(const T& n, const Vec3<T>& v) : x(v.x), y(v.y), z(v.z), w(n)
            {
            }
            
            Quat(const T& wp, const T& xp, const T& yp, const T& zp) : x(xp), y(yp), z(zp), w(wp)
            {
            }
            
            ~Quat()
            {
            }
            
            
            T & operator[](int i)
            {
                return (&x)[i];
            }
            
            T const & operator[](int i) const
            {
                return (&x)[i];
            }
            
            
            // Operators
            Quat<T> & operator+=(Quat<T> const & q)
            {
                x += q.x;
                y += q.y;
                z += q.z;
                w += q.w;
                
                return *this;
            }
            
            Quat<T> & operator*=(T const & q)
            {
                x *= q.x;
                y *= q.y;
                z *= q.z;
                w *= q.w;
                
                return *this;
            }
            
            Quat<T> & operator*=(Quat<T> const & q)
            {
                Quat<T> const p(*this);
                
                w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
                x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
                y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
                z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;
                
                return *this;
            }
            
            Quat<T> & operator/=(T const & s)
            {
                x /= s;
                y /= s;
                z /= s;
                w /= s;
            }
            
            
        };
        
        ////////////////////
        /// Binary operators
        ////////////////////
        
        // operator+
        template <typename T>
        Quat<T> operator+ (const Quat<T>& a, const Quat<T>& b)
        {
            return (Quat<T>(a) += b);
        }
        
        
        
        // operator-
        template <typename T>
        Quat<T> operator- (const Quat<T>& a, const Quat<T>& b)
        {
            return (Quat<T>(a) -= b);
        }
        
        
        
        // operator*
        template <typename T>
        Quat<T> operator* (const Quat<T>& a, const Quat<T>& b)
        {
            return (Quat<T>(a) *= b);
        }
        
        
        template <typename T>
        Quat<T> operator* (const Quat<T>& a, const T& b)
        {
            return (Quat<T>(a) *= b);
        }
        
        
        template <typename T>
        Quat<T> operator* (const T& a, const Quat<T>& b)
        {
            return Quat<T>(a*b.w, a*b.x, a*b.y, a*b.z);
        }
        
        
        template <typename T>
        Vec3<T> operator* (const Quat<T>& q, const Vec3<T>& v)
        {
            Vec3<T> const quatVec(q.x, q.y, q.z);
            Vec3<T> const uv(cross(quatVec, v));
            Vec3<T> const uuv(cross(quatVec, uv));
            
            return v + ((uv * q.w) + uuv) * static_cast<T>(2);
        }
        
        
        template <typename T>
        Vec3<T> operator* (const Vec3<T>& v, const Quat<T>& q)
        {
            return inverse(q) * v;
        }
        
        
        template <typename T>
        Vec4<T> operator* (const Vec4<T>& v, const Quat<T>& q)
        {
            return Vec4<T>(q * Vec3<T>(v.x, v.y, v.z), v.w);
        }
        
        
        template <typename T>
        Vec4<T> operator* (const Quat<T>& q, const Vec4<T>& v)
        {
            return inverse(q) * v;
        }
        
        
        
        // operator/
        
        template <typename T>
        Quat<T> operator/ (const Quat<T>& a, const T& b)
        {
            return (Quat<T>(a) /= b);
        }
        
        
        
        template <typename T>
        bool operator==(Quat<T> const & v1, Quat<T> const & v2)
        {
            return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z) && (v1.w == v2.w);
        }
        
        
        template <typename T>
        bool operator!=(Quat<T> const & v1, Quat<T> const & v2)
        {
            return !(v1 == v2);
        }
        
        
        
        ////////////////////////////
        /// Unary constant operators
        ////////////////////////////
        template <typename T>
        Quat<T> const operator- (Quat<T> const & a)
        {
            return Quat<T>(-a.w, -a.x, -a.y, -a.z);
        }
        
        
        template<typename T = basetype>
        Quat<T> rotation(const Vec3<T>& orig, const Vec3<T>& dest)
        {
            T epsilon(0.00000001);
            T pi(3.141592653589793);
            T cosTheta = dot(orig, dest);
            Vec3<T> rotationAxis;
            
            if(cosTheta < static_cast<T>(-1) + epsilon)
            {
                // special case when vectors in opposite directions :
                // there is no "ideal" rotation axis
                // So guess one; any will do as long as it's perpendicular to start
                // This implementation favors a rotation around the Up axis (Y),
                // since it's often what you want to do.
                rotationAxis = cross(Vec3<T>(0, 0, 1), orig);
                if(length2(rotationAxis) < epsilon) // bad luck, they were parallel, try again!
                    rotationAxis = cross(Vec3<T>(1, 0, 0), orig);
                
                rotationAxis = normalize(rotationAxis);
                return angleAxis(pi, rotationAxis);
            }
            
            // Implementation from Stan Melax's Game Programming Gems 1 article
            rotationAxis = cross(orig, dest);
            
            T s = sqrt((T(1) + cosTheta) * static_cast<T>(2));
            T invs = static_cast<T>(1) / s;
            
            return Quat<T>(s * static_cast<T>(0.5f),
                           rotationAxis.x * invs,
                           rotationAxis.y * invs,
                           rotationAxis.z * invs);
        }
        
        template<typename T = basetype>
        Quat<T> angleAxis(const T& angle, const Vec3<T>& axis)
        {
            Quat<T> result;
            
            T s = sin(angle * T(0.5));
            
            result.w = cos(angle * T(0.5));
            result.x = axis.x * s;
            result.y = axis.y * s;
            result.z = axis.z * s;
                        
            return result;
        }
        
        
        
        template <typename T>
        Quat<T> inverse(Quat<T> const & q)
        {
            return conjugate(q) / dot(q, q);
        }
        
        template <typename T>
        Quat<T> conjugate(Quat<T> const & q)
        {
            return Quat<T>(q.w, -q.x, -q.y, -q.z);
        }
        
        template <typename T>
        T dot(Quat<T> const & q, Quat<T> const & p)
        {
            return q.x * p.x + q.y * p.y + q.z * p.z + q.w * p.w;
        }
        
        template <typename T>
        Quat<T> normalize(const Quat<T>& q)
        {
            T len = length(q);
            if(len <= T(0)) {
                return Quat<T>(1, 0, 0, 0);
            }
            
            T oneOverLen = T(1) / len;
            
            return Quat<T>(q.w * oneOverLen, q.x * oneOverLen, q.y * oneOverLen, q.z * oneOverLen);
        }
        
        template <typename T>
        T length(const Quat<T>& v)
        {
            T sqr = v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
            
            return sqrt(sqr);
        }
        
        template <typename T>
        Mat4<T> mat4_cast(Quat<T> const & q)
        {
            Mat4<T> Result(T(1));
            T qxx(q.x * q.x);
            T qyy(q.y * q.y);
            T qzz(q.z * q.z);
            T qxz(q.x * q.z);
            T qxy(q.x * q.y);
            T qyz(q.y * q.z);
            T qwx(q.w * q.x);
            T qwy(q.w * q.y);
            T qwz(q.w * q.z);
            
            Result[0][0] = 1 - 2 * (qyy +  qzz);
            Result[0][1] = 2 * (qxy + qwz);
            Result[0][2] = 2 * (qxz - qwy);
            Result[0][3] = 0;
            
            Result[1][0] = 2 * (qxy - qwz);
            Result[1][1] = 1 - 2 * (qxx +  qzz);
            Result[1][2] = 2 * (qyz + qwx);
            Result[1][3] = 0;
            
            Result[2][0] = 2 * (qxz + qwy);
            Result[2][1] = 2 * (qyz - qwx);
            Result[2][2] = 1 - 2 * (qxx +  qyy);
            Result[2][3] = 0;
            
            Result[3][0] = 0;
            Result[3][1] = 0;
            Result[3][2] = 0;
            Result[3][3] = 1;
            
            return Result;
        }
        
        
        
        template<typename T>
        Mat4<T> rotate(const Mat4<T> mat, Quat<T> rotation)
        {
            return mat * mat4_cast(rotation);
        }
        
        template<typename T>
        Vec3<T> rotate(const Vec3<T> vec, Quat<T> rotation)
        {
            return rotation * vec;
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


#endif /* defined(__OpenGLFramework__quat__) */
