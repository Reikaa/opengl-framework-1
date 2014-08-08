//
//  graph.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "graph.h"

namespace lkogl {
    namespace scene {
        SceneGraph::SceneGraph() : root_()
        {
        }

        SceneGraph::~SceneGraph()
        {
        }
        
        Group& SceneGraph::root() const {
            return root_;
        }
    }
}