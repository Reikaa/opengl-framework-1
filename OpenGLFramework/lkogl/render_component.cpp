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
            
            void RenderComponent::update(TreeTransformation& transformation) const
            {
            }
            
            void RenderComponent::render(const TreeTransformation& transformation, const graphics::Program& program) const
            {
                graphics::MaterialUse mat(program, model_.material());
                const graphics::GeometryObjectUse geo(model_.geometry());
                graphics::ModelMatrixUse matrix(program, transformation.matrix());
                
                geo.render();
            }
            
            RenderComponent::~RenderComponent()
            {
            }
        }
    }
}