//
//  layout_renderer.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 15.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "layout_renderer.h"
#include "text.h"
#include "scissor.h"

#include <queue>

namespace lkogl {
    namespace ui {
        LayoutRenderer::LayoutRenderer() :
        square_(geometry::primitives::makeSquare()),
        program_(createProgram())
        {}
        
        LayoutRenderer::~LayoutRenderer()
        {}
        
        graphics::shader::Program LayoutRenderer::createProgram() const
        {
            utils::PlainText vshDefGeo("ui-element.vsh");
            utils::PlainText fshDefGeo("ui-element.fsh");
            
            return graphics::shader::Program(vshDefGeo.content, fshDefGeo.content);
        }
        
        void LayoutRenderer::render(std::shared_ptr<Element> e, const graphics::Screen& screen)
        {
            glClearColor(0, 0, 0, 0);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            
            glViewport(0, 0, screen.width, screen.height);
                        
            math::Mat4<float> projection = math::ortho<float>(0,screen.width, 0, screen.height);
            
            graphics::shader::ProgramUse pru(program_);
            
            graphics::GeometryObjectUse sq(square_);
            
            graphics::MainTargetUse s;
            std::queue<std::pair<std::shared_ptr<Element>, Rectangle>> elements;
            
            elements.push({e, e->layout().rectangle()});

            graphics::ScissorUse scissor;
            
            while(!elements.empty()) {
                const std::pair<std::shared_ptr<Element>, Rectangle> current = elements.front();
                elements.pop();
                
                auto rect = current.first->layout().rectangle();
                if(rect.width() > 0 && rect.height() > 0) {
                    math::Mat4<float> modelView(1);
                    math::Mat4<float> modelViewProj = projection;

                    for(auto c : current.first->children()) {
                        elements.push({c, rect});
                    }

                    modelView = math::translate(modelView, {
                        rect.center().x,
                        screen.height-rect.center().y,
                        0.0
                    });
                    
                    modelView = math::scale(modelView, {rect.width()/2, rect.height()/2, 0.0});
                    
                    modelViewProj *= modelView;
                    
                    scissor.clip(current.second.left(),
                              screen.height-current.second.bottom(),
                              current.second.width(),
                              current.second.height());
                    
                    if(current.first->render()) {
                        pru.setUniform("uViewProjMatrix", modelViewProj);
                        
                        Style stl = current.first->style();
                        Color bg = stl.background();
                        
                        if(bg.w) {
                            pru.setUniform("uColor", bg);                            
                            sq.render();
                        }
                    }
                }
            }
        }
    }
}