//
//  node_component.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__node_component__
#define __OpenGLFramework__node_component__

#include <stdio.h>
#include "transform.h"
#include "program.h"

namespace lkogl {
    namespace scene {
        class Component
        {
        public:
            typedef void (Component::*ComponentUpdateMethod)(const geometry::Transform& transformation) const;
            typedef void (Component::*ComponentRenderMethod)(const geometry::Transform& transformation, const graphics::Program&) const;
            
            virtual void update(const geometry::Transform& transformation) const = 0;
            
            virtual void render(const geometry::Transform& transformation, const graphics::Program&) const = 0;
            
            virtual ~Component();
        };
    }
}

#endif /* defined(__OpenGLFramework__node_component__) */
