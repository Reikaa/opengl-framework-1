//
//  entity_transformation.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 25.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./entity_transformation.h"

namespace lkogl {
    namespace scene {
        EntityTransformation::EntityTransformation() {}
        EntityTransformation::~EntityTransformation() {}
        
        void EntityTransformation::setTranslation(const math::Vec3<float>& t)
        {
            transformation_.setTranslation(t);
            dirty_ = true;
        }
        
        void EntityTransformation::setScale(const math::Vec3<float>& s)
        {
            transformation_.setScale(s);
            dirty_ = true;
        }
        
        void EntityTransformation::setRotation(const math::Quat<float>& r)
        {
            transformation_.setRotation(r);
            dirty_ = true;
        }
        
        void EntityTransformation::transform(const geometry::Transformation& t)
        {
            transformation_.transform(t);
            dirty_ = true;
        }

        
        math::Vec3<float> EntityTransformation::translation() const
        {
            return transformation_.translation();
        }
        
        math::Vec3<float> EntityTransformation::scale() const
        {
            return transformation_.scale();
        }
        
        math::Quat<float> EntityTransformation::rotation() const
        {
            return transformation_.rotation();
        }
        
        void EntityTransformation::setParent(const math::Mat4<float>& parent)
        {
            parentTransform_ = parent;
            dirty_ = true;
        }
        
        const math::Mat4<float>& EntityTransformation::matrix() const
        {
            if(dirty_) {
                cacheMatrix_ = parentTransform_ * transformation_.matrix();
                dirty_ = false;
                dirtyInverse_ = true;
            }
            
            return cacheMatrix_;
        }
        
        const math::Mat4<float>& EntityTransformation::inverseMatrix() const
        {
            if(dirty_ || dirtyInverse_) {
                cacheInverse_ = math::inverse(matrix());
                dirtyInverse_ = false;
            }
            
            return cacheInverse_;
        }
    }
}