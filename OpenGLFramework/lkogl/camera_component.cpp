//
//  camera_component.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include <iostream>

#include "camera_component.h"
#include "shader.h"

namespace lkogl {
    namespace scene {
        namespace components {
            CameraComponent::CameraComponent(camera::Camera cam) : camera_(cam)
            {
            }
            
            void CameraComponent::update(const geometry::Transform& transformation) const
            {
            }
            
            void CameraComponent::render(const geometry::Transform& transformation, const graphics::Program& program) const
            {
                graphics::CameraMatrixUse(program, camera_.viewMatrix(), camera_.projection_.matrix(), camera_.position());
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

