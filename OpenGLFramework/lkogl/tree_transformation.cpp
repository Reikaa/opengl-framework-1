//
//  tree_transform.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 12.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "tree_transformation.h"
#include <iostream>

namespace lkogl {
    namespace scene {
        
        TreeTransformation::TreeTransformation() : parent_(NULL), dirty_(false) {
        }
        
        TreeTransformation::TreeTransformation(const TreeTransformation& t) : parent_(t.parent_), relativTransform_(t.relativTransform_)
        {
        }
            
        TreeTransformation::~TreeTransformation() {
        
        }
        
        const Vec3& TreeTransformation::translation() const
        {
            return relativTransform_.translation;
        }
        
        const Vec3& TreeTransformation::scale() const
        {
            return relativTransform_.scale;
        }
        
        const Quat& TreeTransformation::rotation() const
        {
            return relativTransform_.rotation;
        }
        
        
        void TreeTransformation::setTranslation(const Vec3& transl)
        {
            relativTransform_.translation = transl;
            
            dirty_ = true;
        }
        
        void TreeTransformation::setScale(const Vec3& scale)
        {
            relativTransform_.scale = scale;
            
            dirty_ = true;
        }
        
        void TreeTransformation::setRotation(const Quat& rot)
        {
            relativTransform_.rotation = rot;
            
            dirty_ = true;
        }
        
        void TreeTransformation::add(const geometry::Transformation& t) {
            relativTransform_.rotation = math::normalize(relativTransform_.rotation*t.rotation);
            relativTransform_.scale *= t.scale;
            relativTransform_.translation += t.translation;
                        
            dirty_ = true;
        }
        
        bool TreeTransformation::isDirty() const
        {
            return dirty_ || (parent_!=NULL &&  parent_->isDirty());
        }
        
        const Mat4 TreeTransformation::matrix() const {
            if(isDirty()) {
                if(dirty_) {
                    selfMat_ = relativTransform_.matrix();
                    dirty_ = false;
                }
                if(parent_ != NULL) {
                    mat_ = parent_->matrix() * selfMat_;
                } else {
                    mat_ = selfMat_;
                }
            }
            
            return mat_;
        }
    }
}