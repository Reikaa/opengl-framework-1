//
//  transform.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 08.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__transform__
#define __OpenGLFramework__transform__

#include <stdio.h>
#include "mesh.h"

namespace lkogl {
    namespace geometry {
        struct Transform {
            typedef lkogl::math::Quat<GLfloat> Quat;
            
            Vec3 translation = Vec3(0,0,0);
            Vec3 scale = Vec3(1,1,1);
            Quat rotation = lkogl::math::rotation(0, Vec3(0,0,1));
        };
    }
}

#endif /* defined(__OpenGLFramework__transform__) */
