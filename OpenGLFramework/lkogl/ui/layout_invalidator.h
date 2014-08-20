//
//  layout_invalidator.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 16.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__layout_invalidator__
#define __OpenGLFramework__layout_invalidator__

#include "./element.h"

namespace lkogl {
    namespace ui {
        
        class LayoutInvalidator
        {
        public:
            LayoutInvalidator();
            ~LayoutInvalidator();
            
            void invalidate(std::shared_ptr<Element> e) const;
        };
        
    }
}

#endif /* defined(__OpenGLFramework__layout_invalidator__) */
