//
//  node.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__node__
#define __OpenGLFramework__node__

#include "visitor.h"
#include "transform.h"

namespace lkogl {
    namespace scene {
        
        class Node {
        public:
            geometry::Transform transformation;

            virtual ~Node();
            virtual void accept( const Visitor & ) const = 0;
        };
    }
}

#endif /* defined(__OpenGLFramework__node__) */
