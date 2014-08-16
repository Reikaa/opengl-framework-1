//
//  layout_renderer.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 15.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "layout_renderer.h"
#include "text.h"

namespace lkogl {
    namespace ui {
        LayoutRenderer::LayoutRenderer() :
        square_(geometry::primitives::makeSquare()),
        program_(createProgram())
        {}
        
        LayoutRenderer::~LayoutRenderer()
        {}
        
        graphics::Program LayoutRenderer::createProgram() const
        {
            utils::PlainText vshDefGeo("ui-element.vsh");
            utils::PlainText fshDefGeo("ui-element.fsh");
            
            return graphics::Program(vshDefGeo.content, fshDefGeo.content);
        }
        
        void LayoutRenderer::render(const Element& e, const graphics::Screen& screen)
        {
            graphics::MainTargetUse s;
            
            glClearColor(0, 0, 0, 0);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            
            graphics::ProgramUse pru(program_);
            glUniform4f(program_.handles().colorPosition, 0.1, 0.1, 0.1, 0.6);
            
            graphics::GeometryObjectUse sq(square_);
            
            auto rect = e.layout().rectangle();
            if(rect.width() > 0 && rect.height() > 0) {
                glViewport(rect.left(), screen.height-rect.bottom(), rect.width(), rect.height());
                sq.render();
                for(auto c : e.children()) {
                    auto rect = c->layout().rectangle();
                    
                    if(rect.width() > 0 && rect.height() > 0) {
                        glViewport(rect.left(), screen.height-rect.bottom(), rect.width(), rect.height());
                        sq.render();
                    }
                }
            }
        }
    }
}