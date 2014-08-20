//
//  scissor.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 16.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__scissor__
#define __OpenGLFramework__scissor__

#include <stdio.h>


namespace lkogl {
    namespace graphics {
        
        class ScissorUse {
        public:
            ScissorUse();
            void clip(int x, int y, int width, int height);
            ~ScissorUse();
        };
        
    }
}

#endif /* defined(__OpenGLFramework__scissor__) */
