//
//  animation_component.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 12.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__animation_component__
#define __OpenGLFramework__animation_component__

#include "./base_component.h"
#include "../../geometry/transformation.h"

namespace lkogl {
    namespace scene {
        namespace components {
            class AnimationComponent : public Component {
                geometry::Transformation transform_;
                const float speed_;
            public:
                AnimationComponent(const geometry::Transformation&);
                ~AnimationComponent();
                
                void update(Entity& transformation) const override;
                void render(const Entity& transformation, const graphics::shader::ProgramUse&) const override;
            };
        }
    }
}

#endif /* defined(__OpenGLFramework__animation_component__) */
