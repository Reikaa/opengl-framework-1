//
//  render_component.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./render_component.h"
#include "../entity.h"

namespace lkogl {
    namespace scene {
        namespace components {
            RenderComponent::RenderComponent(graphics::GeometryObject geo, graphics::Material mat) :
            geometry_(geo), material_(mat)
            {}
            
            void RenderComponent::update(Entity& e) const
            {
            }
            
            void RenderComponent::render(const Entity& e, const graphics::shader::ProgramUse& program) const
            {
                graphics::MaterialUse mat(program, material_);
                const graphics::GeometryObjectUse geo(geometry_);
                program.setUniform("uModelMatrix", e.transformation().matrix());
                
                geo.render();
            }
            
            RenderComponent::~RenderComponent()
            {
            }
        }
    }
}