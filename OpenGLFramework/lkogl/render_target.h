//
//  render_target.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 13.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__render_target__
#define __OpenGLFramework__render_target__


namespace lkogl {
    namespace graphics {
        struct Screen {
            int width, height;
        };
        
        class ScreenRendering {
        public:
            ScreenRendering(const Screen&, int rw, int rh);
            ~ScreenRendering();
        };
    }
}

#endif /* defined(__OpenGLFramework__render_target__) */
