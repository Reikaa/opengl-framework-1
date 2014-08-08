//
//  scene_renderer.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__scene_renderer__
#define __OpenGLFramework__scene_renderer__

#include <stdio.h>
#include "visitor.h"
#include "group.h"
#include "leaf.h"

namespace lkogl {
    namespace scene {
        namespace visitor {

            class SceneRenderer : public Visitor
            {
            public:
                void visit(const Group&) const;
                void visit(const Leaf&) const;
                
                void leave(const Group&) const;
                void leave(const Leaf&) const;
            };
            
        }
        
    }
}

#endif /* defined(__OpenGLFramework__scene_renderer__) */
