//
//  node.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "node.h"

namespace lkogl {
    namespace scene {
        Node::Node() {
        }
        
        Node::~Node() {
        }
        
        void Node::addChild(std::shared_ptr<Node> n) {
            n->transformation.setParent(&transformation);
            children_.push_back(n);
        }
        
        void Node::addComponent(std::shared_ptr<Component> c) {
            components_.push_back(c);
        }
    }
}