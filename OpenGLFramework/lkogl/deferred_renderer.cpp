//
//  deferred_renderer.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 14.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "deferred_renderer.h"
#include "text.h"
#include "render_target.h"
#include "directional_light.h"
#include "scene_deep_walker.h"
#include "stencil.h"
#include "mesh.h"

namespace lkogl {
    namespace graphics {
        namespace renderign {
            
            DeferredRenderer::DeferredRenderer(int w, int h) :
            programs_(initPrograms()), buffer_(new FrameBuffer(w, h, std::vector<TargetType> {
                TargetType{GL_COLOR_ATTACHMENT0, GL_RGBA16F},
                TargetType{GL_COLOR_ATTACHMENT1, GL_RGBA16F},
                TargetType{GL_COLOR_ATTACHMENT2, GL_RGBA16F},
            })), screen_{w,h}, square_(geometry::primitives::makeSquare())
            {
            }
            
            DeferredRenderer::Programs DeferredRenderer::initPrograms()
            {
                utils::PlainText vshDefGeo("deferred-geometry.vsh");
                utils::PlainText fshDefGeo("deferred-geometry.fsh");
                
                utils::PlainText vshDefPlain("deferred-plain.vsh");
                utils::PlainText fshDefPlain("deferred-plain.fsh");
                
                utils::PlainText vshDefStencil("deferred-stencil.vsh");
                utils::PlainText fshDefStencil("deferred-stencil.fsh");
                
                utils::PlainText vshDefDir("deferred-directional.vsh");
                utils::PlainText fshDefDir("deferred-directional.fsh");
                
                return {
                    Program(vshDefGeo.content, fshDefGeo.content),
                    Program(vshDefPlain.content, fshDefPlain.content),
                    Program(vshDefStencil.content, fshDefStencil.content),
                    Program(vshDefDir.content, fshDefDir.content)
                };
            }
            
            DeferredRenderer::~DeferredRenderer()
            {
            }
            
            void DeferredRenderer::render(std::shared_ptr<scene::Node> graph, const camera::Camera& cam) const
            {
                scene::walker::SceneDeepWalker walker;
                
                {
                    BufferTargetUse tr(*buffer_);
                    
                    glEnable(GL_DEPTH_TEST);
                    glDepthMask(GL_TRUE);
                    glDisable(GL_BLEND);
                    
                    glClearColor(0,0,0,0);
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                    
                    ProgramUse defgeo(programs_.deferredGeo_);
                    walker.walk(graph, &scene::Component::render, programs_.deferredGeo_);
                    
                    glDepthMask(GL_FALSE);
                    glDisable(GL_DEPTH_TEST);
                }
                
                lighting::DirectionalLight light({0.6,0.7,0.9}, 0.9, {1,-1,1});
                lighting::DirectionalLight light2({0.6,0.7,0.9}, 0.9, {-1,-1,-1});
                
                glEnable(GL_BLEND);
                glBlendEquation(GL_FUNC_ADD);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                
                {
                    MainTargetUse s(screen_, 16, 9);
                    
                    glClearColor(0,0.7,0.9,1);
                    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                    
                    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
                    glDepthMask(GL_FALSE);
                    
                    ProgramUse stencil(programs_.deferredStencil_);
                    
                    BufferTextureUse tus(programs_.deferredStencil_.handles().samplerPosition, *buffer_, 2, 2);
                    
                    GeometryObjectUse gu(square_);
                    
                    {
                        StencilCreation c(true);
                        gu.render();
                    }
                    {
                        StencilUse stnu;
                        
                        
                        ProgramUse plain(programs_.deferredPlain_);
                        
                        BufferTextureUse tuc(programs_.deferredPlain_.handles().samplerPosition, *buffer_, 2, 2);
                        
                        gu.render();
                        
                        
                        glBlendFunc(GL_ONE, GL_ONE);
                        
                        ProgramUse directional(programs_.deferredDir_);
                        
                        glUniform3f(programs_.deferredDir_.handles().eyePosition, cam.position().x, cam.position().y, cam.position().z);
                        
                        BufferTextureUse tu1(programs_.deferredDir_.handles().samplerPosPosition, *buffer_, 0, 0);
                        BufferTextureUse tu2(programs_.deferredDir_.handles().samplerNormPosition, *buffer_, 1, 1);
                        BufferTextureUse tu3(programs_.deferredDir_.handles().samplerColPosition, *buffer_, 2, 2);
                        
                        lighting::DirectionalLightUse lightuse(programs_.deferredDir_, light);
                        
                        gu.render();
                        
                        lighting::DirectionalLightUse lightuse2(programs_.deferredDir_, light2);
                        
                        gu.render();
                        
                    }
                    
                }
                
            }
            
            
            void DeferredRenderer::resize(int w, int h)
            {
                screen_.width = w;
                screen_.height = h;
                
                buffer_.reset(new FrameBuffer(w, h, std::vector<TargetType> {
                    TargetType{GL_COLOR_ATTACHMENT0, GL_RGBA16F},
                    TargetType{GL_COLOR_ATTACHMENT1, GL_RGBA16F},
                    TargetType{GL_COLOR_ATTACHMENT2, GL_RGBA16F},
                }));
            }
        }
    }
}