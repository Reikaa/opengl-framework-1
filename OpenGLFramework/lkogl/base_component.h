//
//  node_component.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__node_component__
#define __OpenGLFramework__node_component__

#include "tree_transformation.h"
#include "program.h"

namespace lkogl {
    namespace scene {
        namespace components {
            class Component
            {
            public:
                typedef void (Component::*ComponentUpdateMethod)(TreeTransformation& transformation) const;
                typedef void (Component::*ComponentRenderMethod)(const TreeTransformation& transformation, const graphics::Program&) const;
                
                virtual void update(TreeTransformation& transformation) const = 0;
                
                virtual void render(const TreeTransformation& transformation, const graphics::Program&) const = 0;
                
                virtual ~Component();
            };
        }
    }
}

#endif /* defined(__OpenGLFramework__node_component__) */
