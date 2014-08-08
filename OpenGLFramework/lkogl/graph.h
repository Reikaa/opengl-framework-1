//
//  graph.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__graph__
#define __OpenGLFramework__graph__

#include "group.h"

namespace lkogl {
    namespace scene {
        class SceneGraph {
            mutable Group root_;
        public:

            SceneGraph();
            ~SceneGraph();
            
            Group& root() const;
        };
    }
}

#endif /* defined(__OpenGLFramework__graph__) */
