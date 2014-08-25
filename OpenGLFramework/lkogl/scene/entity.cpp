//
//  entity.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 24.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./entity.h"

namespace lkogl {
    namespace scene {
        Entity::Entity()
        {
        }
        
        Entity::~Entity()
        {
        }
        
            
        void Entity::addComponent(std::shared_ptr<components::Component> c)
        {
            components_.push_back(c);
        }
        
        const std::vector<std::shared_ptr<components::Component>>& Entity::components() const
        {
            return components_;
        }
            
        void Entity::setTransformation(const EntityTransformation& t)
        {
            transformation_ = t;
        }
        
        const EntityTransformation& Entity::transformation() const
        {
            return transformation_;
        }
        
        EntityTransformation& Entity::transformation()
        {
            return transformation_;
        }
        
        void Entity::setBounding(const math::geo::Aabb3<float>& b)
        {
            bounding_ = b;
        }
        
        const math::geo::Aabb3<float>& Entity::bounding() const
        {
            return bounding_;
        }
        
    }
}