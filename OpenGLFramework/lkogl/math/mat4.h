//
//  mat4.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 08.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__mat4__
#define __OpenGLFramework__mat4__

#include "./vec4.h"

namespace lkogl {
    namespace math {
        typedef float basetype;
        
        template <typename T = basetype>
        struct Mat4 {
        private:
            Vec4<T> col[4];
        public:
            Mat4() : Mat4(1)
            {
            }
            
            explicit Mat4(const T& val) :
            col{
                Vec4<T>(val, 0, 0, 0),
                Vec4<T>(0, val, 0, 0),
                Vec4<T>(0, 0, val, 0),
                Vec4<T>(0, 0, 0, val)
            }
            {
            }
            
            explicit Mat4(const Vec4<T>& scale) :
            col{
                Vec4<T>(scale[0], 0, 0, 0),
                Vec4<T>(0, scale[1], 0, 0),
                Vec4<T>(0, 0, scale[2], 0),
                Vec4<T>(0, 0, 0, scale[3])
            }
            {
            }
            
            Mat4(const Mat4<T>& o) :
            col{
                Vec4<T>(o[0]),
                Vec4<T>(o[1]),
                Vec4<T>(o[2]),
                Vec4<T>(o[3])
            }
            {
            }
            
            Mat4(const Vec4<T>& c1, const Vec4<T>& c2, const Vec4<T>& c3, const Vec4<T>& c4) :
            col{
                Vec4<T>(c1),
                Vec4<T>(c2),
                Vec4<T>(c3),
                Vec4<T>(c4)
            }
            {
            }
            
            ~Mat4()
            {
            }
            
            
            Vec4<T> & operator[](int i)
            {
                return col[i];
            }
            
            Vec4<T> const & operator[](int i) const
            {
                return col[i];
            }
            
            // Unary updatable operators
            Mat4<T> & operator= (Mat4<T> const & m)
            {
                col[0] = m.col[0];
                col[1] = m.col[1];
                col[2] = m.col[2];
                col[3] = m.col[3];
                
                return *this;
            }
            
            Mat4<T> & operator+= (T s)
            {
                col[0] += s;
                col[1] += s;
                col[2] += s;
                col[3] += s;
                
                return *this;
            }
            
            Mat4<T> & operator+= (Mat4<T> const & m)
            {
                col[0] += m.col[0];
                col[1] += m.col[1];
                col[2] += m.col[2];
                col[3] += m.col[3];
                
                return *this;
            }
            
            Mat4<T> & operator-= (T s)
            {
                col[0] -= s;
                col[1] -= s;
                col[2] -= s;
                col[3] -= s;
                
                return *this;
            }
            
            Mat4<T> & operator-= (Mat4<T> const & m)
            {
                col[0] -= m.col[0];
                col[1] -= m.col[1];
                col[2] -= m.col[2];
                col[3] -= m.col[3];
                
                return *this;
            }
            
            Mat4<T> & operator*= (T s)
            {
                col[0] *= s;
                col[1] *= s;
                col[2] *= s;
                col[3] *= s;
                                
                return *this;
            }
            
            Mat4<T> & operator*= (Mat4<T> const & m)
            {
                return (*this = *this * m);
            }
            
            Mat4<T> & operator/= (T s)
            {
                col[0] /= s;
                col[1] /= s;
                col[2] /= s;
                col[3] /= s;
            }
            
//            Mat4<T> & operator/= (Mat4<T> const & m)
//            {
//            }
            
            //////////////////////////////////////
            // Increment and decrement operators
            
            Mat4<T> & operator++ ()
            {
                ++col[0];
                ++col[1];
                ++col[2];
                ++col[3];
                
                return *this;
            }
            
            Mat4<T> & operator-- ()
            {
                --col[0];
                --col[1];
                --col[2];
                --col[3];
                
                return *this;
            }
            
            Mat4<T> operator++(int)
            {
                Mat4<T> result(*this);
                
                ++*this;
                
                return result;
            }
            
            Mat4<T> operator--(int)
            {
                Mat4<T> result(*this);
                
                --*this;
                
                return result;
            }
            
        };
        
        // Binary operators
        template <typename T>
        Mat4<T> operator+ (Mat4<T> const & m, T const & s)
        {
            return (Mat4<T>(*m) += s);
        }
        
        template <typename T>
        Mat4<T> operator+ (T const & s, Mat4<T> const & m)
        {
            return (Mat4<T>(*m) += s);
        }
        
        template <typename T>
        Mat4<T> operator+ (Mat4<T> const & m1, Mat4<T> const & m2)
        {
            return (Mat4<T>(*m1) += m2);
        }
        
        template <typename T>
        Mat4<T> operator- (Mat4<T> const & m, T const & s)
        {
            return (Mat4<T>(*m) -= s);
        }
        
        template <typename T>
        Mat4<T> operator- (T const & s, Mat4<T> const & m)
        {
            return (-Mat4<T>(*m) += s);
        }
        
        template <typename T>
        Mat4<T> operator- (Mat4<T> const & m1, Mat4<T> const & m2)
        {
            return (Mat4<T>(*m1) -= m2);
        }
        
        template <typename T>
        Mat4<T> operator* (Mat4<T> const & m, T const & s)
        {
            return (Mat4<T>(m) *= s);
        }
        
        template <typename T>
        Mat4<T> operator* (T const & s, Mat4<T> const & m)
        {
            return (Mat4<T>(m) *= s);
        }
        
        template <typename T>
        Vec4<T> operator* (Mat4<T> const & m, Vec4<T> const & v)
        {
            Vec4<T> const Mov0(v[0]);
            Vec4<T> const Mov1(v[1]);
            Vec4<T> const Mul0 = m[0] * Mov0;
            Vec4<T> const Mul1 = m[1] * Mov1;
            Vec4<T> const Add0 = Mul0 + Mul1;
            Vec4<T> const Mov2(v[2]);
            Vec4<T> const Mov3(v[3]);
            Vec4<T> const Mul2 = m[2] * Mov2;
            Vec4<T> const Mul3 = m[3] * Mov3;
            Vec4<T> const Add1 = Mul2 + Mul3;
            Vec4<T> const Add2 = Add0 + Add1;
            return Add2;
        }
        
        template <typename T>
        Vec4<T> operator* (Vec4<T> const & v,  Mat4<T> const & m)
        {
            return Vec4<T>(
                m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2] + m[0][3] * v[3],
                m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2] + m[1][3] * v[3],
                m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2] + m[2][3] * v[3],
                m[3][0] * v[0] + m[3][1] * v[1] + m[3][2] * v[2] + m[3][3] * v[3]
            );
        }
        
        template <typename T>
        Mat4<T> operator* (Mat4<T> const & m1, Mat4<T> const & m2)
        {
            Vec4<T> const SrcA0 = m1[0];
            Vec4<T> const SrcA1 = m1[1];
            Vec4<T> const SrcA2 = m1[2];
            Vec4<T> const SrcA3 = m1[3];
            
            Vec4<T> const SrcB0 = m2[0];
            Vec4<T> const SrcB1 = m2[1];
            Vec4<T> const SrcB2 = m2[2];
            Vec4<T> const SrcB3 = m2[3];
            
            Mat4<T> Result(0);
            Result[0] = SrcA0 * SrcB0[0] + SrcA1 * SrcB0[1] + SrcA2 * SrcB0[2] + SrcA3 * SrcB0[3];
            Result[1] = SrcA0 * SrcB1[0] + SrcA1 * SrcB1[1] + SrcA2 * SrcB1[2] + SrcA3 * SrcB1[3];
            Result[2] = SrcA0 * SrcB2[0] + SrcA1 * SrcB2[1] + SrcA2 * SrcB2[2] + SrcA3 * SrcB2[3];
            Result[3] = SrcA0 * SrcB3[0] + SrcA1 * SrcB3[1] + SrcA2 * SrcB3[2] + SrcA3 * SrcB3[3];
            
            return Result;
        }
        
        template <typename T>
        Mat4<T> operator/ (Mat4<T> const & m, T const & s)
        {
            return (Mat4<T>(m)/=s);
        }
        
        template <typename T>
        Mat4<T> operator/ (T const & s, Mat4<T> const & m)
        {
            return Mat4<T>(
                s / m[0],
                s / m[1],
                s / m[2],
                s / m[3]);
        }
        
        
        // Unary constant operators
        template <typename T>
        Mat4<T> const operator- (Mat4<T> const & m)
        {
            return Mat4<T>(-m[0], -m[1], -m[2], -m[3]);
        }


        template<typename T>
        Mat4<T> inverse(const Mat4<T>& m)
        {
            T Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
            T Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
            T Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
            
            T Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
            T Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
            T Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
            
            T Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
            T Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
            T Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
            
            T Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
            T Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
            T Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
            
            T Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
            T Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
            T Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];
            
            T Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
            T Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
            T Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];
            
            Vec4<T> Fac0(Coef00, Coef00, Coef02, Coef03);
            Vec4<T> Fac1(Coef04, Coef04, Coef06, Coef07);
            Vec4<T> Fac2(Coef08, Coef08, Coef10, Coef11);
            Vec4<T> Fac3(Coef12, Coef12, Coef14, Coef15);
            Vec4<T> Fac4(Coef16, Coef16, Coef18, Coef19);
            Vec4<T> Fac5(Coef20, Coef20, Coef22, Coef23);
            
            Vec4<T> Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
            Vec4<T> Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
            Vec4<T> Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
            Vec4<T> Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);
            
            Vec4<T> Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
            Vec4<T> Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
            Vec4<T> Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
            Vec4<T> Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);
            
            Vec4<T> SignA(+1, -1, +1, -1);
            Vec4<T> SignB(-1, +1, -1, +1);
            Mat4<T> Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);
            
            Vec4<T> Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);
            
            Vec4<T> Dot0(m[0] * Row0);
            T Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);
            
            T OneOverDeterminant = static_cast<T>(1) / Dot1;
            
            return Inverse * OneOverDeterminant;
        }
        
        template <typename T>
        Mat4<T> lookAt(Vec3<T> const & eye, Vec3<T> const & center, Vec3<T> const & up)
        {
            Vec3<T> f(normalize(center - eye));
            Vec3<T> s(normalize(cross(f, up)));
            Vec3<T> u(cross(s, f));
            
            Mat4<T> Result(1);
            Result[0][0] = s.x;
            Result[1][0] = s.y;
            Result[2][0] = s.z;
            Result[0][1] = u.x;
            Result[1][1] = u.y;
            Result[2][1] = u.z;
            Result[0][2] =-f.x;
            Result[1][2] =-f.y;
            Result[2][2] =-f.z;
            Result[3][0] =-dot(s, eye);
            Result[3][1] =-dot(u, eye);
            Result[3][2] = dot(f, eye);
            return Result;
        }
        
        template<typename T>
        Mat4<T> scale(const Mat4<T> mat, T factor)
        {
            return Mat4<T>(
                           factor * mat[0],
                           factor * mat[1],
                           factor * mat[2],
                           mat[3]
                           );
        }
        
        template<typename T>
        Mat4<T> scale(const Mat4<T> mat, Vec3<T> factor)
        {
            return Mat4<T>(
                           factor.x * mat[0],
                           factor.y * mat[1],
                           factor.z * mat[2],
                           mat[3]
                           );
        }
        
        template<typename T>
        Mat4<T> translate(const Mat4<T> mat, Vec3<T> offset)
        {
            return Mat4<T>(
                           mat[0],
                           mat[1],
                           mat[2],
                           mat[3] + Vec4<T>(offset, 0)
                           );
        }
    }
}

#endif /* defined(__OpenGLFramework__mat4__) */
