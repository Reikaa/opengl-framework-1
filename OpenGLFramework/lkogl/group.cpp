//
//  group.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "group.h"

namespace lkogl {
    namespace scene {
        void Group::add(std::shared_ptr<Node> n) {
            children_.push_back(n);
        }
        
        void Group::accept( const Visitor &v ) const {
            v.visit(*this);
            for(auto n : children_) {
                n->accept(v);
            }
            v.leave(*this);
        }
    }
}