//
//  scene_renderer.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "scene_renderer.h"

namespace lkogl {
    namespace scene {
        namespace visitor {
            
            void SceneRenderer::visit(const Group& group) const
            {
                
            }
            
            void SceneRenderer::visit(const Leaf& leaf) const
            {
                graphics::Model m = leaf.model();
            }
            
            void SceneRenderer::leave(const Group& group) const
            {
                
            }
            
            void SceneRenderer::leave(const Leaf& leaf) const
            {
                
            }
            
        }
        
    }
}