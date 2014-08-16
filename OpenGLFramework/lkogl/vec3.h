//
//  vec3.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 08.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__vec3__
#define __OpenGLFramework__vec3__

#include <math.h>

namespace lkogl {
    namespace math {
        typedef float basetype;
        
        template <typename T = basetype>
        struct Vec3 {
            T x, y, z;
            
            Vec3() : x(0), y(0), z(0)
            {
            }
            
            Vec3(const Vec3<T>& o) : x(o.x), y(o.y), z(o.z)
            {
            }
            
            Vec3(const T& xp, const T& yp, const T& zp) : x(xp), y(yp), z(zp)
            {
            }
            
            explicit Vec3(const T& v) : x(v), y(v), z(v)
            {
            }
            
            ~Vec3()
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
            
            
            Vec3<T> & operator= (Vec3<T> const & other)
            {
                x = other.x;
                y = other.y;
                z = other.z;
                
                return *this;
            }
            
            
            Vec3<T> & operator+= (T s)
            {
                x += s;
                y += s;
                z += s;
                
                return *this;
            }
            
            
            Vec3<T> & operator+= (Vec3<T> const & m)
            {
                x += m.x;
                y += m.y;
                z += m.z;
                
                return *this;
            }
            
            
            Vec3<T> & operator-= (T s)
            {
                x -= s;
                y -= s;
                z -= s;
                
                return *this;
            }
            
            
            Vec3<T> & operator-= (Vec3<T> const & m)
            {
                x -= m.x;
                y -= m.y;
                z -= m.z;
                
                return *this;
            }
            
            
            Vec3<T> & operator*= (T s)
            {
                x *= s;
                y *= s;
                z *= s;
                
                return *this;
            }
            
            
            Vec3<T> & operator*= (Vec3<T> const & m)
            {
                x *= m.x;
                y *= m.y;
                z *= m.z;
                
                return *this;
            }
            
            
            Vec3<T> & operator/= (T s)
            {
                x /= s;
                y /= s;
                z /= s;
                
                return *this;
            }
            
            
            Vec3<T> & operator/= (Vec3<T> const & m)
            {
                x /= m.x;
                y /= m.y;
                z /= m.z;
                
                return *this;
            }
            
            
            Vec3<T> & operator++ ()
            {
                ++x;
                ++y;
                ++z;
                
                return *this;
            }
            
            Vec3<T> & operator-- ()
            {
                --x;
                --y;
                --z;
                
                return *this;
            }
            
            Vec3<T> operator++(int)
            {
                Vec3<T> result(*this);
                ++*this;
                
                return result;
            }
            
            Vec3<T> operator--(int)
            {
                Vec3<T> result(*this);
                --*this;
                
                return result;
            }
            
            
        };
        
        
        ////////////////////
        /// Binary operators
        ////////////////////
        
        // operator+
        template <typename T>
        Vec3<T> operator+ (const Vec3<T>& a, const Vec3<T>& b)
        {
            return (Vec3<T>(a) += b);
        }
        
        
        template <typename T>
        Vec3<T> operator+ (const Vec3<T>& a, const T& b)
        {
            return (Vec3<T>(a) += b);
        }
        
        
        template <typename T>
        Vec3<T> operator+ (const T& a, const Vec3<T>& b)
        {
            return (Vec3<T>(b) += a);
        }
        
        
        
        // operator-
        template <typename T>
        Vec3<T> operator- (const Vec3<T>& a, const Vec3<T>& b)
        {
            return (Vec3<T>(a) -= b);
        }
        
        
        template <typename T>
        Vec3<T> operator- (const Vec3<T>& a, const T& b)
        {
            return (Vec3<T>(a) -= b);
        }
        
        
        template <typename T>
        Vec3<T> operator- (const T& a, const Vec3<T>& b)
        {
            return Vec3<T>(a-b.x, a-b.y, a-b.z);
        }
        
        
        
        // operator*
        template <typename T>
        Vec3<T> operator* (const Vec3<T>& a, const Vec3<T>& b)
        {
            return (Vec3<T>(a) *= b);
        }
        
        
        template <typename T>
        Vec3<T> operator* (const Vec3<T>& a, const T& b)
        {
            return (Vec3<T>(a) *= b);
        }
        
        
        template <typename T>
        Vec3<T> operator* (const T& a, const Vec3<T>& b)
        {
            return (Vec3<T>(b) *= a);
        }
        
        
        
        // operator/
        template <typename T>
        Vec3<T> operator/ (const Vec3<T>& a, const Vec3<T>& b)
        {
            return (Vec3<T>(a) /= b);
        }
        
        
        template <typename T>
        Vec3<T> operator/ (const Vec3<T>& a, const T& b)
        {
            return (Vec3<T>(a) /= b);
        }
        
        
        template <typename T>
        Vec3<T> operator/ (const T& a, const Vec3<T>& b)
        {
            return Vec3<T>(a/b.x, a/b.y, a/b.z);
        }
        
        
        
        // operator==
        template <typename T>
        bool operator==(Vec3<T> const & v1, Vec3<T> const & v2)
        {
            return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
        }
        
        
        template <typename T>
        bool operator!=(Vec3<T> const & v1, Vec3<T> const & v2)
        {
            return !(v1==v2);
        }
        
        
        ////////////////////////////
        /// Unary constant operators
        ////////////////////////////
        template <typename T>
        Vec3<T> const operator- (Vec3<T> const & a)
        {
            return Vec3<T>(-a.x, -a.y, -a.z);
        }
        
        template <typename T>
        Vec3<T>cross(const Vec3<T>& a, const Vec3<T>& b)
        {
            return Vec3<T>(a.y * b.z - b.y * a.z,
                           a.z * b.x - b.z * a.x,
                           a.x * b.y - b.x * a.y);
        }
        
        template <typename T>
        T dot(Vec3<T> const & q, Vec3<T> const & p)
        {
            return q.x * p.x + q.y * p.y + q.z * p.z;
        }
        
        template <typename T>
        T length(const Vec3<T>& v)
        {
            return sqrt(length2(v));
        }
        
        template <typename T>
        T length2(const Vec3<T>& v)
        {
            return dot(v,v);
        }
        
        template <typename T>
        T max(const Vec3<T>& v)
        {
            return std::max(v.x, std::max(v.y, v.z));
        }
        
        template <typename T>
        Vec3<T> normalize(const Vec3<T>& v)
        {
            T len = length(v);
            if(len <= T(0)) {
                return Vec3<T>(0, 0, 0);
            }
            
            T oneOverLen = T(1) / len;
            
            return Vec3<T>(v.x * oneOverLen, v.y * oneOverLen, v.z * oneOverLen);
        }
        
        template <typename T>
        Vec3<T> max(const Vec3<T>& a, const Vec3<T>& b)
        {
            return {
                std::max(a.x, b.x),
                std::max(a.y, b.y),
                std::max(a.z, b.z)
            };
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
        
    }
}

#endif /* defined(__OpenGLFramework__vec3__) */
