//
//  render_component.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__render_component__
#define __OpenGLFramework__render_component__

#include <stdio.h>
#include "node_component.h"
#include "model.h"

namespace lkogl {
    namespace scene {
        namespace components {
            class RenderComponent : public Component {
                graphics::Model model_;
            public:
                RenderComponent(graphics::Model m);
                ~RenderComponent();

                void update(TreeTransformation& transformation) const override;
                void render(const TreeTransformation& transformation, const graphics::Program&) const override;
            };
        }
    }
}

#endif /* defined(__OpenGLFramework__render_component__) */