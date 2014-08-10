//
//  scene_renderer.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__scene_renderer__
#define __OpenGLFramework__scene_renderer__

#include "math.h"
#include "opengl.h"

#include "node_component.h"
#include "node.h"

namespace lkogl {
    namespace scene {
        namespace walker {
            class SceneDeepWalker
            {
            public:
                SceneDeepWalker();
                ~SceneDeepWalker();
           
                void walk(const std::shared_ptr<Node>, Component::ComponentUpdateMethod) const;
                void walk(const std::shared_ptr<Node>, Component::ComponentRenderMethod, const graphics::Program&) const;
            };
            
        }
        
    }
}

#endif /* defined(__OpenGLFramework__scene_renderer__) */
