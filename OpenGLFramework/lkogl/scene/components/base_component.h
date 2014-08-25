//
//  node_component.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__node_component__
#define __OpenGLFramework__node_component__

#include "../../graphics/shader/program.h"

namespace lkogl {
    namespace scene {
        class Entity;
        
        namespace components {
            class Component
            {
            public:
                typedef void (Component::*ComponentUpdateMethod)(Entity&) const;
                typedef void (Component::*ComponentRenderMethod)(const Entity&, const graphics::shader::ProgramUse&) const;
                
                virtual void update(Entity& transformation) const = 0;
                
                virtual void render(const Entity& transformation, const graphics::shader::ProgramUse&) const = 0;
                
                virtual ~Component();
            };
        }
    }
}

#endif /* defined(__OpenGLFramework__node_component__) */
