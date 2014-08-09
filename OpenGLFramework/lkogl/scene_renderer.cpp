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
                viewMatrix_ = math::lookAt(math::Vec3<GLfloat>(3,0,4), math::Vec3<GLfloat>(1,1,1), math::Vec3<GLfloat>(0,1,0));
                projectionMatrix_ = math::perspective(math::radians(65.0f), 16/9.0f, 2.f, 100.f);
                cameraPosition_ = math::Vec3<GLfloat>(3,0,4);
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
                graphics::MatrixUse matrix(m.material().program(), leaf.transformation.matrix(), viewMatrix_, projectionMatrix_, cameraPosition_);
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