//
//  frustum3.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 21.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__frustum3__
#define __OpenGLFramework__frustum3__

#include <array>

#include "../quat.h"
#include "../vec3.h"
#include "../mat4.h"

#include "./plane3.h"

namespace lkogl {
    namespace math {
        namespace elements {
        
            
            template <typename T>
            struct Frustum3
            {
                // plane normals are pointing to the outside
                struct {
                    Plane3<T> left;
                    Plane3<T> right;
                    Plane3<T> top;
                    Plane3<T> bottom;
                    Plane3<T> near;
                    Plane3<T> far;
                } planes;
                
                Frustum3() {}
                
                Frustum3(T const & fovy, T const & aspectX, T const & aspectY, T const & zNear, T const & zFar)
                {
                    T aspect = static_cast<T>(aspectX/(double)aspectY);
                    T fovx = 2*atan(aspect*tan(fovy/2.0));
                    
                    planes.left = Plane3<T>(rotate({-1,0,0}, angleAxis(fovx/2, {0,1,0})), {0,0,0});
                    planes.right = Plane3<T>(rotate({1,0,0}, angleAxis(-fovx/2, {0,1,0})), {0,0,0});
                    
                    
                    planes.top = Plane3<T>(rotate({0,1,0}, angleAxis(fovy/2, {1,0,0})), {0,0,0});
                    planes.bottom = Plane3<T>(rotate({0,-1,0}, angleAxis(-fovy/2, {1,0,0})), {0,0,0});
                    
                    planes.near = Plane3<T>({0,0,1}, -zNear);
                    planes.far = Plane3<T>({0,0,-1}, zFar);
                }
                
                T verticalAngle() const {
                    return acos(dot(planes.top.normal, -planes.bottom.normal));
                }
                
                T horizontalAngle() const {
                    return acos(dot(planes.left.normal, -planes.right.normal));
                }
                                
                ~Frustum3() {}
                
                std::array<Plane3<T>, 6> faces() const {
                    std::array<Plane3<T>, 6> faces;
                    
                    faces[0] = planes.left;
                    faces[1] = planes.right;
                    faces[2] = planes.top;
                    faces[3] = planes.bottom;
                    faces[4] = planes.near;
                    faces[5] = planes.far;
                    
                    return faces;
                }
                
                std::array<Vec3<T>, 8> corners() const {
                    std::array<Vec3<T>, 8> corners;
                    
                    return {
                        intersection(planes.left, planes.top, planes.near),
                        intersection(planes.left, planes.bottom, planes.near),
                        intersection(planes.right, planes.top, planes.near),
                        intersection(planes.right, planes.bottom, planes.near),
                        intersection(planes.right, planes.bottom, planes.far),
                        intersection(planes.right, planes.top, planes.far),
                        
                        intersection(planes.left, planes.bottom, planes.far),
                        intersection(planes.left, planes.top, planes.far),
                    };
                }
            };
            
            template<typename T>
            Mat4<T> mat_cast(const Frustum3<T>& f)
            {
                Mat4<T> result(0);
                std::array<Vec3<T>, 8> corners = f.corners();
                Vec3<T> leftTop = corners[0];
                Vec3<T> rightBottom = corners[3];
                T near = -corners[0].z;
                T far = -corners[7].z;
                T left = leftTop.x;
                T right = rightBottom.x;
                T top = leftTop.y;
                T bottom = rightBottom.y;
                
                result[0][0] = (2*near)/(right-left);
                result[1][1] = (2*near)/(top-bottom);
                
                result[2][0] =  (right+left)/(right-left);
                result[2][2] = -(far+near)/(far-near);
                result[2][3] =  -1;
                
                result[3][2] =  -(2*far*near)/(far-near);
                
                return result;
            }
            
            template<typename T>
            Frustum3<T> frustum_from_view_projection(Mat4<T> mat)
            {
                
                Frustum3<T> frustum;
                
                Plane3<T> left(-math::Vec3<float>{
                    mat[0][3] + mat[0][0],
                    mat[1][3] + mat[1][0],
                    mat[2][3] + mat[2][0]},
                               
                    (mat[3][3] + mat[3][0]));
                left.normalize();
                
                Plane3<T> right(-math::Vec3<float>{
                    mat[0][3] - mat[0][0],
                    mat[1][3] - mat[1][0],
                    mat[2][3] - mat[2][0]},
                    
                    (mat[3][3] - mat[3][0]));
                right.normalize();
                
                Plane3<T> bottom(-math::Vec3<float>{
                    mat[0][3] + mat[0][1],
                    mat[1][3] + mat[1][1],
                    mat[2][3] + mat[2][1]},
                              
                    (mat[3][3] + mat[3][1]));
                bottom.normalize();
                
                Plane3<T> top(-math::Vec3<float>{
                    mat[0][3] - mat[0][1],
                    mat[1][3] - mat[1][1],
                    mat[2][3] - mat[2][1]},
                                 
                    (mat[3][3] - mat[3][1]));
                top.normalize();
                
                Plane3<T> near(-math::Vec3<float>{
                    mat[0][3] + mat[0][2],
                    mat[1][3] + mat[1][2],
                    mat[2][3] + mat[2][2]},
                    
                    (mat[3][3] + mat[3][2]));
                near.normalize();
                
                Plane3<T> far(-math::Vec3<float>{
                    mat[0][3] - mat[0][2],
                    mat[1][3] - mat[1][2],
                    mat[2][3] - mat[2][2]},
                              
                    (mat[3][3] - mat[3][2]));
                far.normalize();
            
                frustum.planes = {
                    left,
                    right,
                    top,
                    bottom,
                    near,
                    far
                };
                
                return frustum;
            }
            
        }
    }
}

#endif /* defined(__OpenGLFramework__frustum3__) */
