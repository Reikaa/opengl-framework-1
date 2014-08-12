//
//  tree_transform.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 12.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "tree_transform.h"
#include <iostream>

namespace lkogl {
    namespace scene {
        
        TreeTransform::TreeTransform() : parent_(NULL), dirty_(false) {
        }
        
        TreeTransform::TreeTransform(const TreeTransform& t) : parent_(t.parent_), relativTransform_(t.relativTransform_)
        {
        }
            
        TreeTransform::~TreeTransform() {
        
        }
        
        const Vec3& TreeTransform::translation() const
        {
            return relativTransform_.translation;
        }
        
        const Vec3& TreeTransform::scale() const
        {
            return relativTransform_.scale;
        }
        
        const Quat& TreeTransform::rotation() const
        {
            return relativTransform_.rotation;
        }
        
        
        void TreeTransform::setTranslation(const Vec3& transl)
        {
            relativTransform_.translation = transl;
            
            dirty_ = true;
        }
        
        void TreeTransform::setScale(const Vec3& scale)
        {
            relativTransform_.scale = scale;
            
            dirty_ = true;
        }
        
        void TreeTransform::setRotation(const Quat& rot)
        {
            relativTransform_.rotation = rot;
            
            dirty_ = true;
        }
        
        bool TreeTransform::isDirty() const
        {
            return dirty_ || (parent_!=NULL &&  parent_->isDirty());
        }
        
        const Mat4 TreeTransform::matrix() const {
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