//
//  entity.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 24.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__entity__
#define __OpenGLFramework__entity__

#include <vector>

#include "../math/math.h"
#include "../math/elements.h"
#include "./components/base_component.h"
#include "./entity_transformation.h"

namespace lkogl {
    namespace scene {
        class Entity {
            std::vector<std::shared_ptr<components::Component>> components_;
            EntityTransformation transformation_;
            math::geo::Aabb3<float> bounding_;
        public:
            Entity();
            ~Entity();
            
            void addComponent(std::shared_ptr<components::Component>);
            const std::vector<std::shared_ptr<components::Component>>& components() const;
            
            void setTransformation(const EntityTransformation&);
            const EntityTransformation& transformation() const;
            EntityTransformation& transformation();
            
            void setBounding(const math::geo::Aabb3<float>&);
            const math::geo::Aabb3<float>& bounding() const;
        };
    }
}

#endif /* defined(__OpenGLFramework__entity__) */
