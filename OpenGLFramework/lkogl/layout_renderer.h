//
//  layout_renderer.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 15.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__layout_renderer__
#define __OpenGLFramework__layout_renderer__

#include <stdio.h>
#include "element.h"
#include "program.h"
#include "render_target.h"
#include "geometry_object.h"

namespace lkogl {
    namespace ui {
        class LayoutRenderer {
            graphics::Program program_;
            graphics::GeometryObject square_;
        public:
            LayoutRenderer();
            ~LayoutRenderer();
            
            void render(const Element& e, const graphics::Screen& screen);
        private:
            graphics::Program createProgram() const;
        };
    }
}

#endif /* defined(__OpenGLFramework__layout_renderer__) */
