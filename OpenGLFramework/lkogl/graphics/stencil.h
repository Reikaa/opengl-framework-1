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
        
        class Stencil {
        public:
            Stencil();
            ~Stencil();
            
            void filter(int ref) const;
        };
        
    }
}

#endif /* defined(__OpenGLFramework__stencil__) */
