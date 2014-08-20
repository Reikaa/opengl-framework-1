//
//  first_person_movement.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__first_person_movement__
#define __OpenGLFramework__first_person_movement__

#include "../../camera/camera.h"
#include "../../scene/tree_transformation.h"

namespace lkogl {
    namespace input {
        namespace movement {
            class FirstPersonMovement {
                const math::Vec3<float> up_{0,1,0};
                const math::Vec3<float> forward_{0,0,1};
                const math::Vec3<float> sideward_{1,0,0};
                bool fly_ = false;
            public:
                FirstPersonMovement();
                
                void rotateHorizontally(scene::TreeTransformation& cam, float rad) const;
                
                void rotateVertically(scene::TreeTransformation& cam, float rad) const;
                
                void move(scene::TreeTransformation& cam, math::Vec2<float> dir2d, float amoun) const;
                
                void lookAt(scene::TreeTransformation& cam, math::Vec3<float> target) const;
                
                void setFly(bool);
                bool canFly() const;
            };
        }
    }
}

#endif /* defined(__OpenGLFramework__first_person_movement__) */
