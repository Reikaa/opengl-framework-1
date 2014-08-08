//
//  scene_renderer.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "scene_renderer.h"
#include "material.h"

namespace lkogl {
    namespace scene {
        namespace visitor {
            
            SceneRenderer::SceneRenderer()
            {
                cameraPosition_ = math::Vec3<GLfloat>(0,0,4);
                modelMatrix_ = math::scale(modelMatrix_, 8.f);
            }
            
            SceneRenderer::~SceneRenderer()
            {
            }
            
            void SceneRenderer::visit(const Group& group) const
            {
                
            }
            
            void SceneRenderer::visit(const Leaf& leaf) const
            {
                const graphics::Model& m = leaf.model();
                
                graphics::MaterialUse mat(m.material());
                graphics::MatrixUse matrix(m.material().program(), modelMatrix_, viewMatrix_, projectionMatrix_, cameraPosition_);
                graphics::GeometryObjectUse geo(m.geometry());
                
                geo.render();
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