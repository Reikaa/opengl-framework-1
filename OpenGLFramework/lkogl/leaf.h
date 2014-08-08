//
//  leaf.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__leaf__
#define __OpenGLFramework__leaf__

#include <stdio.h>

#include "node.h"
#include "model.h"

namespace lkogl {
    namespace scene {
        class Leaf : public Node {
            graphics::Model model_;
        public:
            Leaf(graphics::Model model);
            ~Leaf();
            graphics::Model model() const;
            void accept( const Visitor & ) const;
        };
    }
}

#endif /* defined(__OpenGLFramework__leaf__) */
