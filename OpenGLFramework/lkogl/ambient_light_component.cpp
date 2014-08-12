//
//  ambient_light_component.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "ambient_light_component.h"

namespace lkogl {
    namespace scene {
        namespace components {
            AmbientLightComponent::AmbientLightComponent(graphics::lighting::AmbientLight light) : light_(light)
            {
            }
            
            void AmbientLightComponent::update(TreeTransformation& transformation) const
            {
            }
            
            void AmbientLightComponent::render(const TreeTransformation& transformation, const graphics::Program& program) const
            {
                graphics::lighting::AmbientLightUse(program, light_);
            }
            
            AmbientLightComponent::~AmbientLightComponent()
            {
            }
        }
    }
}
