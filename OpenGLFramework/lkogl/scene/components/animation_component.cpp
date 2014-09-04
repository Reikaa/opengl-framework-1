//
//  animation_component.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 12.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./animation_component.h"
#include "../entity.h"

namespace lkogl {
    namespace scene {
        namespace components {
            AnimationComponent::AnimationComponent(const geometry::Transformation& t) : transform_(t), speed_(1)
            {
            }
            
            void AnimationComponent::update(Entity& e) const
            {
                e.transformation().transform(transform_);
                
                e.invalidateBoundingBox();
            }
            
            void AnimationComponent::render(const Entity& e, const graphics::shader::ProgramUse& program) const
            {
            }
            
            AnimationComponent::~AnimationComponent()
            {
            }
        }
    }
}
