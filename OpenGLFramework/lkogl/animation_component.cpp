//
//  animation_component.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 12.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "animation_component.h"

namespace lkogl {
    namespace scene {
        namespace components {
            AnimationComponent::AnimationComponent(geometry::Transformation t) : transform_(t), speed_(1)
            {
            }
            
            void AnimationComponent::update(TreeTransformation& transformation) const
            {
                transformation.add(transform_);
            }
            
            void AnimationComponent::render(const TreeTransformation& transformation, const graphics::ProgramUse& program) const
            {
            }
            
            AnimationComponent::~AnimationComponent()
            {
            }
        }
    }
}
