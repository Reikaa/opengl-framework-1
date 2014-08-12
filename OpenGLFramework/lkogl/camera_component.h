//
//  camera_component.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__camera_component__
#define __OpenGLFramework__camera_component__

#include "node_component.h"
#include "camera.h"


namespace lkogl {
    namespace scene {
        namespace components {
            class CameraComponent : public Component {
                camera::Camera camera_;
            public:
                CameraComponent(camera::Camera cam);
                ~CameraComponent();
                
                camera::Camera& camera();
                
                void update(const TreeTransform& transformation) const;
                void render(const TreeTransform& transformation, const graphics::Program&) const;
            };
        }
    }
}

#endif /* defined(__OpenGLFramework__camera_component__) */