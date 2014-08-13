//
//  render_target.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 13.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "render_target.h"
#include "opengl.h"

namespace lkogl {
    namespace graphics {
        
        
        ScreenRendering::ScreenRendering(const Screen& screen, int ratioWidth, int rationHeight)
        {
            if (screen.height * ratioWidth > screen.width * rationHeight) {
                int newWidth = screen.height * ratioWidth / rationHeight;
                glViewport(-(newWidth - screen.width) / 2, 0, newWidth,
                           screen.height);
            } else {
                int newHeight = screen.width * rationHeight / ratioWidth;
                glViewport(0, -(newHeight - screen.height) / 2,
                           screen.width, newHeight);
            }
        }
        
        ScreenRendering::~ScreenRendering()
        {
        }
    }
}