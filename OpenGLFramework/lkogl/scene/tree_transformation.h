//
//  tree_transform.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 12.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__tree_transform__
#define __OpenGLFramework__tree_transform__

#include "../geometry/transformation.h"

namespace lkogl {
    namespace scene {
        
        typedef lkogl::math::Quat<GLfloat> Quat;
        typedef lkogl::math::Mat4<GLfloat> Mat4;
        typedef lkogl::math::Vec3<GLfloat> Vec3;
        
        class TreeTransformation {
            geometry::Transformation relativTransform_;
            const TreeTransformation* parent_;
            mutable Mat4 selfMat_;
            mutable Mat4 mat_;
            mutable Mat4 inverse_;
            mutable bool dirty_ = true;
            
        public:
            TreeTransformation();
            TreeTransformation(const TreeTransformation&);
            ~TreeTransformation();
            
            void setParent(const TreeTransformation* p, bool keepAbsolute = true);
            
            const Vec3& translation() const;
            const Vec3& scale() const;
            const Quat& rotation() const;
            
            void setTranslation(const Vec3&);
            void setScale(const Vec3&);
            void setRotation(const Quat&);
            
            void transform(const geometry::Transformation& t);
            
            const Mat4 matrix() const;
            const Mat4 inverseMatrix() const;
        
            
        private:
            bool isDirty() const;
        };
    }
}

#endif /* defined(__OpenGLFramework__tree_transform__) */
