//
//  scene_renderer.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./scene_deep_walker.h"
#include "../../graphics/material.h"

namespace lkogl {
    namespace scene {
        namespace walker {
            
            SceneDeepWalker::SceneDeepWalker()
            {
                
            }
            
            SceneDeepWalker::~SceneDeepWalker()
            {
            }
            
            void SceneDeepWalker::walk(const std::shared_ptr<Node> node, components::Component::ComponentUpdateMethod m) const
            {
                for(const std::shared_ptr<components::Component> c : node->components_) {
                    (&*c->*m)(node->transformation);
                }
                
                for(std::shared_ptr<Node> n : node->children_) {
                    walk(n, m);
                }
            }
            
            void SceneDeepWalker::walk(const std::shared_ptr<Node> node, components::Component::ComponentRenderMethod m, const graphics::shader::ProgramUse& program) const
            {
                for(const std::shared_ptr<components::Component> c : node->components_) {
                    (&*c->*m)(node->transformation, program);
                }
                
                for(std::shared_ptr<Node> n : node->children_) {
                    walk(n, m, program);
                }
            }

            
        }
        
    }
}