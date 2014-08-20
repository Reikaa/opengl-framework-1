//
//  scene_renderer.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__scene_renderer__
#define __OpenGLFramework__scene_renderer__

#include "base_component.h"
#include "node.h"

namespace lkogl {
    namespace scene {
        namespace walker {
            class SceneDeepWalker
            {
            public:
                SceneDeepWalker();
                ~SceneDeepWalker();
           
                void walk(const std::shared_ptr<Node>, components::Component::ComponentUpdateMethod) const;
                void walk(const std::shared_ptr<Node>, components::Component::ComponentRenderMethod, const graphics::shader::ProgramUse&) const;
            };
            
        }
        
    }
}

#endif /* defined(__OpenGLFramework__scene_renderer__) */
