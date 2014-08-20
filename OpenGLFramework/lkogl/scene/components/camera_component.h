//
//  camera_component.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__camera_component__
#define __OpenGLFramework__camera_component__

#include "./base_component.h"
#include "../../camera/camera.h"


namespace lkogl {
    namespace scene {
        namespace components {
            class CameraComponent : public Component {
                mutable camera::Camera camera_;
            public:
                CameraComponent(camera::Camera cam);
                ~CameraComponent();
                
                camera::Camera& camera();
                
                void update(TreeTransformation& transformation) const override;
                void render(const TreeTransformation& transformation, const graphics::shader::ProgramUse&) const override;
            };
        }
    }
}

#endif /* defined(__OpenGLFramework__camera_component__) */