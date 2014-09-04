//
//  camera_component.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include <iostream>

#include "./camera_component.h"
#include "../entity.h"

namespace lkogl {
    namespace scene {
        namespace components {
            CameraComponent::CameraComponent(camera::Camera cam) : camera_(cam)
            {
            }
            
            void CameraComponent::update(Entity& e) const
            {
                auto mat = e.transformation().matrix();
                camera_.setViewMatrixAndPos(e.transformation().inverseMatrix(), {
                    mat[3][0],
                    mat[3][1],
                    mat[3][2]
                });
                
                e.invalidateBoundingBox();
            }
            
            void CameraComponent::render(const Entity& e, const graphics::shader::ProgramUse& program) const
            {
            }
            
            camera::Camera& CameraComponent::camera()
            {
                return camera_;
            }
        
            CameraComponent::~CameraComponent()
            {
            }
        }
    }
}

