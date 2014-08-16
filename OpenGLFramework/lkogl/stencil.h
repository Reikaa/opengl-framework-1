//
//  stencil.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 14.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__stencil__
#define __OpenGLFramework__stencil__

namespace lkogl {
    namespace graphics {
        
        class StencilCreation {
        public:
            StencilCreation(bool clear);
            ~StencilCreation();
        };
        
        class StencilUse {
            public:
            StencilUse();
            ~StencilUse();
        };
        
    }
}

#endif /* defined(__OpenGLFramework__stencil__) */
