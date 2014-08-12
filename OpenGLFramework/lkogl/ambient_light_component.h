//
//  ambient_light_component.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__ambient_light_component__
#define __OpenGLFramework__ambient_light_component__

#include "node_component.h"
#include "ambient_light.h"

namespace lkogl {
    namespace scene {
        namespace components {
            class AmbientLightComponent : public Component {
                graphics::lighting::AmbientLight light_;
            public:
                AmbientLightComponent(graphics::lighting::AmbientLight light);
                ~AmbientLightComponent();
                
                void update(const TreeTransform& transformation) const;
                void render(const TreeTransform& transformation, const graphics::Program&) const;
            };
        }
    }
}

#endif /* defined(__OpenGLFramework__ambient_light_component__) */
