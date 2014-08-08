//
//  group.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__group__
#define __OpenGLFramework__group__

#include <list>

#include "node.h"

namespace lkogl {
    namespace scene {
        class Group : public Node {
            mutable std::list<std::shared_ptr<Node>> children_;
            
        public:
            void add(std::shared_ptr<Node>);
            std::list<std::shared_ptr<Node>> children() const { return children_; }
            
            void accept( const Visitor & ) const;
        };
        
    }
}

#endif /* defined(__OpenGLFramework__group__) */
