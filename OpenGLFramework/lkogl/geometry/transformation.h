//
//  transformation.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 08.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__transform__
#define __OpenGLFramework__transform__

#include "./mesh.h"

namespace lkogl {
    namespace geometry {
        struct Transformation {
            typedef lkogl::math::Quat<GLfloat> Quat;
            typedef lkogl::math::Mat4<GLfloat> Mat4;
            typedef lkogl::math::Vec3<GLfloat> Vec3;
            
            Vec3 translation_ = Vec3(0.0);
            Vec3 scale_ = Vec3(1);
            Quat rotation_ = math::angleAxis(0.f, Vec3(0,1,0));
            
            const Mat4 matrix() const;
            
            void setTranslation(const Vec3& t) { translation_ = t; }
            void setScale(const Vec3& s) { scale_ = s; }
            void setRotation(const Quat& r) { rotation_ = r; }
            
            Vec3 translation() const { return translation_; }
            Vec3 scale() const { return scale_; }
            Quat rotation() const { return rotation_; }
            
            void transform(const geometry::Transformation& t);
        };
    }
}

#endif /* defined(__OpenGLFramework__transform__) */
