//
//  visitor.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__visitor__
#define __OpenGLFramework__visitor__

#include <stdio.h>

namespace lkogl {
    namespace scene {
        class Visitor {
        public:
            virtual ~Visitor();
            virtual void visit(const class Group & ) const = 0;
            virtual void leave(const class Group & ) const= 0;
            
            virtual void visit(const class Leaf & ) const= 0;
            virtual void leave(const class Leaf & ) const= 0;
        };
    }
}

#endif /* defined(__OpenGLFramework__visitor__) */
