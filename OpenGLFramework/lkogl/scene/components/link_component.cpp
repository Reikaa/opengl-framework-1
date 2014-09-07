//
//  link_component.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 25.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./link_component.h"
#include "../entity.h"

namespace lkogl {
    namespace scene {
        namespace components {
            LinkComponent::LinkComponent(std::shared_ptr<const Entity> t) : linkedTo_(t)
            {
            }
            
            void LinkComponent::update(Entity& e) const
            {
                if(linked_ && active) {
                    e.transformation().setParent(linkedTo_->transformation().matrix(), false);
                } else if(linked_ && !active) {
                    e.transformation().setParent(math::Mat4<float>(1), true);
                    linked_ = false;
                } else if(active) {
                    e.transformation().setParent(linkedTo_->transformation().matrix(), true);
                    linked_ = true;
                } else {
                    return;
                }
                
                e.invalidateBoundingBox();
            }
            
            void LinkComponent::render(const Entity& e, const graphics::shader::ProgramUse& program) const
            {
            }
            
            LinkComponent::~LinkComponent()
            {
            }
        }
    }
}