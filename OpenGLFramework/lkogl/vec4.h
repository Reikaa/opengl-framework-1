//
//  vec4.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 08.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__vec4__
#define __OpenGLFramework__vec4__

namespace lkogl {
    namespace math {
        typedef float basetype;
        
        template <typename T = basetype>
        struct Vec4 {
            T x, y, z, w;
            
            Vec4() : x(0), y(0), z(0), w(0)
            {
            }
            
            Vec4(const Vec4<T>& o) : x(o.x), y(o.y), z(o.z), w(o.w)
            {
            }
            
            Vec4(const Vec3<T>& o, T wp) : x(o.x), y(o.y), z(o.z), w(wp)
            {
            }
            
            Vec4(const T& xp, const T& yp, const T& zp, const T& wp) : x(xp), y(yp), z(zp), w(wp)
            {
            }
            
            
            explicit Vec4(const T& v) : x(v), y(v), z(v), w(v)
            {
            }
            
            ~Vec4()
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
            
            
            Vec4<T> & operator= (Vec4<T> const & o)
            {
                x = o.x;
                y = o.y;
                z = o.z;
                w = o.w;
                
                return *this;
            }
            
            
            Vec4<T> & operator+= (T s)
            {
                x += s;
                y += s;
                z += s;
                w += s;
                
                return *this;
            }
            
            
            Vec4<T> & operator+= (Vec4<T> const & m)
            {
                x += m.x;
                y += m.y;
                z += m.z;
                w += m.w;
                
                return *this;
            }
            
            
            Vec4<T> & operator-= (T s)
            {
                x -= s;
                y -= s;
                z -= s;
                w -= s;
                
                return *this;
            }
            
            
            Vec4<T> & operator-= (Vec4<T> const & m)
            {
                x -= m.x;
                y -= m.y;
                z -= m.z;
                w -= m.w;
                
                return *this;
            }
            
            
            Vec4<T> & operator*= (T s)
            {
                x *= s;
                y *= s;
                z *= s;
                w *= s;
                
                return *this;
            }
            
            
            Vec4<T> & operator*= (Vec4<T> const & m)
            {
                x *= m.x;
                y *= m.y;
                z *= m.z;
                w *= m.w;
                
                return *this;
            }
            
            
            Vec4<T> & operator/= (T s)
            {
                x /= s;
                y /= s;
                z /= s;
                w /= s;
                
                return *this;
            }
            
            
            Vec4<T> & operator/= (Vec4<T> const & m)
            {
                x /= m.x;
                y /= m.y;
                z /= m.z;
                w /= m.w;
                
                return *this;
            }
            
            
            Vec4<T> & operator++ ()
            {
                ++x;
                ++y;
                ++z;
                ++w;
                
                return *this;
            }
            
            Vec4<T> & operator-- ()
            {
                --x;
                --y;
                --z;
                --w;
                
                return *this;
            }
            
            Vec4<T> operator++(int)
            {
                Vec4<T> result(*this);
                ++*this;
                
                return result;
            }
            
            Vec4<T> operator--(int)
            {
                Vec4<T> result(*this);
                --*this;
                
                return result;
            }
            
            
        };
        
        
        ////////////////////
        /// Binary operators
        ////////////////////
        
        // operator+
        template <typename T>
        Vec4<T> operator+ (const Vec4<T>& a, const Vec4<T>& b)
        {
            return (Vec4<T>(a)+=b);
        }
        
        
        template <typename T>
        Vec4<T> operator+ (const Vec4<T>& a, const T& b)
        {
            return (Vec4<T>(a)+=b);
        }
        
        
        template <typename T>
        Vec4<T> operator+ (const T& a, const Vec4<T>& b)
        {
            return (Vec4<T>(b)+=a);
        }
        
        
        
        // operator-
        template <typename T>
        Vec4<T> operator- (const Vec4<T>& a, const Vec4<T>& b)
        {
            return (Vec4<T>(a)-=b);
        }
        
        
        template <typename T>
        Vec4<T> operator- (const Vec4<T>& a, const T& b)
        {
            return (Vec4<T>(a)-=b);
        }
        
        
        template <typename T>
        Vec4<T> operator- (const T& a, const Vec4<T>& b)
        {
            return Vec4<T>(a-b.x, a-b.y, a-b.z, a-b.w);
        }
        
        
        
        // operator*
        template <typename T>
        Vec4<T> operator* (const Vec4<T>& a, const Vec4<T>& b)
        {
            return (Vec4<T>(a)*=b);
        }
        
        
        template <typename T>
        Vec4<T> operator* (const Vec4<T>& a, const T& b)
        {
            return (Vec4<T>(a)*=b);
        }
        
        
        template <typename T>
        Vec4<T> operator* (const T& a, const Vec4<T>& b)
        {
            return Vec4<T>(a*b.x, a*b.y, a*b.z, a*b.w);
        }
        
        
        
        // operator/
        template <typename T>
        Vec4<T> operator/ (const Vec4<T>& a, const Vec4<T>& b)
        {
            return (Vec4<T>(a)/=b);
        }
        
        
        template <typename T>
        Vec4<T> operator/ (const Vec4<T>& a, const T& b)
        {
            return (Vec4<T>(a)/=b);
        }
        
        
        template <typename T>
        Vec4<T> operator/ (const T& a, const Vec4<T>& b)
        {
            return Vec4<T>(a/b.x, a/b.y, a/b.z, a/b.w);
        }
        
        
        
        // operator==
        template <typename T>
        bool operator==(Vec4<T> const & v1, Vec4<T> const & v2)
        {
            return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z) && (v1.w == v2.w);
        }
        
        
        template <typename T>
        bool operator!=(Vec4<T> const & v1, Vec4<T> const & v2)
        {
            return !(v1==v2);
        }
        
        
        ////////////////////////////
        /// Unary constant operators
        ////////////////////////////
        template <typename T>
        Vec4<T> const operator- (Vec4<T> const & a)
        {
            return Vec4<T>(-a.x, -a.y, -a.z, -a.w);
        }
        
        
        template <typename T>
        T dot(Vec4<T> const & q, Vec4<T> const & p)
        {
            return q.x * p.x + q.y * p.y + q.z * p.z + q.w * p.w;
        }
        
        template <typename T>
        T length(const Vec4<T>& v)
        {
            return sqrt(length2(v));
        }
        
        template <typename T>
        T length2(const Vec4<T>& v)
        {
            return dot(v,v);
        }
        
        template <typename T>
        T max(const Vec4<T>& v)
        {
            return std::max(std::max(v.x, v.y), std::max(v.z, v.w));
        }
        
        template <typename T>
        Vec4<T> normalize(const Vec4<T>& v)
        {
            T len = length(v);
            if(len <= T(0)) {
                return Vec4<T>(0, 0, 0, 0);
            }
            
            T oneOverLen = T(1) / len;
            
            return Vec4<T>(v.x * oneOverLen, v.y * oneOverLen, v.z * oneOverLen, v.w * oneOverLen);
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
        
    }
}

#endif /* defined(__OpenGLFramework__vec4__) */
