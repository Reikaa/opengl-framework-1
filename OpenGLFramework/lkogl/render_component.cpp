//
//  render_component.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include <iostream>

#include "render_component.h"

namespace lkogl {
    namespace scene {
        namespace components {
            RenderComponent::RenderComponent(graphics::Model m) : model_(std::move(m))
            {}
            
            void RenderComponent::update(const geometry::Transform& transformation) const
            {
            }
            
            void RenderComponent::render(const geometry::Transform& transformation, const graphics::Program& program) const
            {
                graphics::MaterialUse mat(model_.material());
                graphics::GeometryObjectUse geo(model_.geometry());
                graphics::ModelMatrixUse matrix(program, transformation.matrix());
                
                geo.render();
            }
            
            RenderComponent::~RenderComponent()
            {
            }
        }
    }
}