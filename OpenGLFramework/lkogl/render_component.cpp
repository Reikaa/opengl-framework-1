//
//  render_component.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "render_component.h"

namespace lkogl {
    namespace scene {
        namespace components {
            RenderComponent::RenderComponent(graphics::GeometryObject geo, graphics::Material mat) :
            geometry_(geo), material_(mat)
            {}
            
            void RenderComponent::update(TreeTransformation& transformation) const
            {
            }
            
            void RenderComponent::render(const TreeTransformation& transformation, const graphics::shader::ProgramUse& program) const
            {
                graphics::MaterialUse mat(program, material_);
                const graphics::GeometryObjectUse geo(geometry_);
                program.setUniform("uModelMatrix", transformation.matrix());
                
                geo.render();
            }
            
            RenderComponent::~RenderComponent()
            {
            }
        }
    }
}