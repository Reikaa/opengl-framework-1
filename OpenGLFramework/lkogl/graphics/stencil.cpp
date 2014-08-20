//
//  stencil.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 14.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./stencil.h"
#include "../opengl.h"

namespace lkogl {
    namespace graphics {
        
        StencilCreation::StencilCreation(bool clear)
        {
            glEnable(GL_STENCIL_TEST);
            glClearStencil(0);
            glClear(GL_STENCIL_BUFFER_BIT);
        
            
            glStencilFunc(GL_ALWAYS, 1, 1);
            glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
            
            glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
            glDepthMask(GL_FALSE);
        }
        
        StencilCreation::~StencilCreation()
        {
            glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
            glDepthMask(GL_TRUE);
            
            glDisable(GL_STENCIL_TEST);
        }
        
        
        
        StencilUse::StencilUse()
        {
            glEnable(GL_STENCIL_TEST);
            glStencilFunc(GL_EQUAL, 1, 1);
            glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        }
        
        StencilUse::~StencilUse()
        {
            glDisable(GL_STENCIL_TEST);
        }
        
    }
}