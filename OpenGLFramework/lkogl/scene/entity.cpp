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
        
        void Entity::setBoundingSize(const math::elements::Aabb3<float>& b)
        {
            boundingSize_ = b;
        }
        
        const math::elements::Aabb3<float>& Entity::boundingSize() const
        {
            return boundingSize_;
        }
        
        const math::elements::Aabb3<float> Entity::boundingBox() const
        {
            return math::elements::transformed(boundingSize_, transformation_.matrix());
        }
        
    }
}