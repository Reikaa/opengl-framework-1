//
//  scene_renderer.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__scene_renderer__
#define __OpenGLFramework__scene_renderer__

#include "visitor.h"
#include "group.h"
#include "leaf.h"
#include "math.h"

namespace lkogl {
    namespace scene {
        namespace visitor {

            class SceneRenderer : public Visitor
            {
                math::Mat4<GLfloat> modelMatrix_;
                math::Mat4<GLfloat> viewMatrix_ = math::lookAt(math::Vec3<GLfloat>(4,10,16), math::Vec3<GLfloat>(1,1,1), math::Vec3<GLfloat>(0,1,0));
                math::Mat4<GLfloat> projectionMatrix_ = math::perspective(math::radians(65.0f), 16/9.0f, 2.f, 100.f);
                math::Vec3<GLfloat> cameraPosition_;
            public:
                SceneRenderer();
                ~SceneRenderer();
                void visit(const Group&) const;
                void visit(const Leaf&) const;
                
                void leave(const Group&) const;
                void leave(const Leaf&) const;
            };
            
        }
        
    }
}

#endif /* defined(__OpenGLFramework__scene_renderer__) */
