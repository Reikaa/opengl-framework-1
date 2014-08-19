//
//  camera_component.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "camera_component.h"

namespace lkogl {
    namespace scene {
        namespace components {
            CameraComponent::CameraComponent(camera::Camera cam) : camera_(cam)
            {
            }
            
            void CameraComponent::update(TreeTransformation& transformation) const
            {
                auto mat = transformation.matrix();
                camera_.setViewMatrixAndPos(transformation.inverseMatrix(), {
                    mat[3][0],
                    mat[3][1],
                    mat[3][2]
                });
            }
            
            void CameraComponent::render(const TreeTransformation& transformation, const graphics::shader::ProgramUse& program) const
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

