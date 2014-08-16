//
//  scissor.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 16.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "scissor.h"
#include "opengl.h"

namespace lkogl {
    namespace graphics {

        ScissorUse::ScissorUse()
        {
            glEnable(GL_SCISSOR_TEST);
        }
        
        void ScissorUse::clip(int x, int y, int width, int height)
        {
            glScissor(x,y,width,height);
        }
        
        ScissorUse::~ScissorUse()
        {
            glDisable(GL_SCISSOR_TEST);
        }
        
    }
}