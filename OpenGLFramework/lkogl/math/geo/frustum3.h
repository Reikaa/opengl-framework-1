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
        namespace geo {
        
            
            template <typename T>
            struct Frustum3
            {
                struct {
                    Plane3<T> left;
                    Plane3<T> right;
                    Plane3<T> top;
                    Plane3<T> bottom;
                    Plane3<T> near;
                    Plane3<T> far;
                } planes;
                
                Frustum3() {}
                Frustum3(const Mat4<T>& mat) { SetFromMatrx(mat); }
                ~Frustum3() {}
                
                void SetFromMatrx(const Mat4<T>& mat)
                {
                
                    planes.left.setNormalConstant(Vec3<T>(mat[0][3] - mat[0][0], mat[1][3] - mat[1][0], mat[2][3] - mat[2][0]), mat[3][3] - mat[3][0]);
                    planes.left.normalize();
                    
                    planes.right.setNormalConstant({mat[0][3] + mat[0][0], mat[1][3] + mat[1][0], mat[2][3] + mat[2][0]}, mat[3][3] + mat[3][0]);
                    planes.right.normalize();
                    
                    planes.top.setNormalConstant({mat[0][3] + mat[0][1], mat[1][3] + mat[1][1], mat[2][3] + mat[2][1]}, mat[3][3] + mat[3][1]);
                    planes.top.normalize();
                
                    planes.bottom.setNormalConstant({mat[0][3] - mat[0][1], mat[1][3] - mat[1][1], mat[2][3] - mat[2][1]}, mat[3][3] - mat[3][1]);
                    planes.bottom.normalize();
                    
                    planes.near.setNormalConstant({mat[0][3] - mat[0][2], mat[1][3] - mat[1][2], mat[2][3] - mat[2][2]}, mat[3][3] - mat[3][2]);
                    planes.near.normalize();
                    
                    planes.far.setNormalConstant({mat[0][3] + mat[0][2], mat[1][3] + mat[1][2], mat[2][3] + mat[2][2]}, mat[3][3] + mat[3][2]);
                    planes.far.normalize();
                }
                
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
            };
            
        }
    }
}

#endif /* defined(__OpenGLFramework__frustum3__) */
