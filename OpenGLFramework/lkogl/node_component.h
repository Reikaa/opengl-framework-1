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
#include "tree_transform.h"
#include "program.h"

namespace lkogl {
    namespace scene {
        class Component
        {
        public:
            typedef void (Component::*ComponentUpdateMethod)(const TreeTransform& transformation) const;
            typedef void (Component::*ComponentRenderMethod)(const TreeTransform& transformation, const graphics::Program&) const;
            
            virtual void update(const TreeTransform& transformation) const = 0;
            
            virtual void render(const TreeTransform& transformation, const graphics::Program&) const = 0;
            
            virtual ~Component();
        };
    }
}

#endif /* defined(__OpenGLFramework__node_component__) */
