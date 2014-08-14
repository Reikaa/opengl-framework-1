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
        
        void TreeTransformation::setParent(const TreeTransformation* p, bool keepAbsolute) {
            if(keepAbsolute) {
                math::Mat4<float> prev;
                math::Mat4<float> next;
                math::Mat4<float> self = relativTransform_.matrix();
                
                if(parent_ != 0) {
                    prev = parent_->matrix();
                }
                if(p != 0) {
                    next = p->matrix();
                }
                
                math::Mat4<float> abs = math::inverse(next) * prev * self;
                relativTransform_.translation = {abs[3][0], abs[3][1], abs[3][2]};
                relativTransform_.rotation = math::normalize(math::quat_cast(abs));
                relativTransform_.scale = {math::length(abs[0]),math::length(abs[1]),math::length(abs[2])};
            }
            
            parent_ = p;
            dirty_ = true;
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
            return dirty_ || (parent_ &&  parent_->isDirty());
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
                inverse_ = math::inverse(mat_);
            }
            
            return mat_;
        }
        
        const Mat4 TreeTransformation::inverseMatrix() const {
            if(isDirty()) {
                matrix();
            }
            return inverse_;
        }
    }
}