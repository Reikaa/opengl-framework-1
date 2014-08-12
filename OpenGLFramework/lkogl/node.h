//
//  node.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__node__
#define __OpenGLFramework__node__


#include <list>
#include <vector>
#include "tree_transform.h"
#include "node_component.h"

namespace lkogl {
    namespace scene {
        
        namespace walker {
            class SceneDeepWalker;
        }
        
        class Node {
            mutable std::list<std::shared_ptr<Node>> children_;
            mutable std::vector<std::shared_ptr<Component>> components_;

        public:
            TreeTransform transformation;

            Node();
            ~Node();
            
            void addChild(std::shared_ptr<Node>);
            void addComponent(std::shared_ptr<Component>);
            
            friend class walker::SceneDeepWalker;
        };
    }
}

#endif /* defined(__OpenGLFramework__node__) */
