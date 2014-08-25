//
//  link_component.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 25.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__link_component__
#define __OpenGLFramework__link_component__

#include "./base_component.h"
#include "../../geometry/transformation.h"

namespace lkogl {
    namespace scene {
        namespace components {
            class LinkComponent : public Component {
                std::shared_ptr<const Entity> linkedTo_;
                mutable bool linked_ = false;
            public:
                LinkComponent(std::shared_ptr<const Entity>);
                ~LinkComponent();
                
                void update(Entity& transformation) const override;
                void render(const Entity& transformation, const graphics::shader::ProgramUse&) const override;
                
                bool active = true;
            };
        }
    }
}

#endif /* defined(__OpenGLFramework__link_component__) */
