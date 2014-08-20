//
//  deferred_renderer.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 14.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./deferred_renderer.h"
#include "../../utils/text.h"
#include "../render_target.h"
#include "../lighting/directional_light.h"
#include "../lighting/ambient_light.h"
#include "../../scene/walker/scene_deep_walker.h"
#include "../stencil.h"
#include "../../geometry/mesh.h"

#include <iostream>

namespace lkogl {
    namespace graphics {
        namespace rendering {
            
            DeferredRenderer::DeferredRenderer(const Screen& s, int ratioWidth, int ratioHeight) :
            programs_(initPrograms()), buffer_(new FrameBuffer(s.width, s.height, std::vector<TargetType> {
                TargetType{GL_COLOR_ATTACHMENT0, GL_RGBA16F},
                TargetType{GL_COLOR_ATTACHMENT1, GL_RGBA16F},
                TargetType{GL_COLOR_ATTACHMENT2, GL_RGBA16F},
            })), square_(geometry::primitives::makeSquare()), ratioWidth_(ratioWidth), ratioHeight_(ratioHeight)
            {
            }
            
            DeferredRenderer::Programs DeferredRenderer::initPrograms()
            {
                utils::PlainText vshDefGeo("deferred-geometry.vsh");
                utils::PlainText fshDefGeo("deferred-geometry.fsh");
                
                utils::PlainText vshDefPlain("deferred-ambient.vsh");
                utils::PlainText fshDefPlain("deferred-ambient.fsh");
                
                utils::PlainText vshDefStencil("deferred-stencil.vsh");
                utils::PlainText fshDefStencil("deferred-stencil.fsh");
                
                utils::PlainText vshDefDir("deferred-directional.vsh");
                utils::PlainText fshDefDir("deferred-directional.fsh");
                
                return {
                    shader::Program(vshDefGeo.content, fshDefGeo.content),
                    shader::Program(vshDefPlain.content, fshDefPlain.content),
                    shader::Program(vshDefStencil.content, fshDefStencil.content),
                    shader::Program(vshDefDir.content, fshDefDir.content)
                };
            }
            
            DeferredRenderer::~DeferredRenderer()
            {
            }
            
            void DeferredRenderer::render(std::shared_ptr<scene::Node> graph, const camera::Camera& cam) const
            {
                scene::walker::SceneDeepWalker walker;
                
                std::vector<lighting::DirectionalLight> directionalLights = {
                    lighting::DirectionalLight({0.6,0.7,0.9}, 0.4, {-0.3,1,-0.3}),
                    lighting::DirectionalLight({0.6,0.7,0.9}, 0.4, {1,-0.3,1}),
                    lighting::DirectionalLight({1,1,1}, 1.4, {0,-1,0}),
                };
                
                lighting::AmbientLight ambientLight({0.1,0.1,0.1});
                
                
                // Geometry Pass
                {
                    BufferTargetUse tr(*buffer_);
                    
                    glViewport(viewport_.x, viewport_.y, viewport_.width, viewport_.height);
                    
                    glEnable(GL_DEPTH_TEST);
                    glDepthMask(GL_TRUE);
                    glDisable(GL_BLEND);
                    
                    glClearColor(1,0,0,0);
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                    
                    shader::ProgramUse defgeo(programs_.deferredGeo_);
                    
                    auto matrix = cam.viewProjectionMatrix();
                    defgeo.setUniform("uViewProjMatrix", matrix);
                    defgeo.setUniformf("uFar", cam.perspective().far());

                    walker.walk(graph, &scene::components::Component::render, defgeo);
                    
                    glDepthMask(GL_FALSE);
                    glDisable(GL_DEPTH_TEST);
                }
                
                MainTargetUse s;
                glViewport(0, 0, screen_.width, screen_.height);
                
                glEnable(GL_BLEND);
                glBlendEquation(GL_FUNC_ADD);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                glClearColor(0,0.7,0.9,1);
                glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                
                GeometryObjectUse squareObj(square_);
                
                {
                    StencilCreation stencil(true);

                    shader::ProgramUse stencilProg(programs_.deferredStencil_);
                    BufferTextureUse tus(stencilProg, "uSampler", *buffer_, 0, 0);
                    
                    squareObj.render();
                }
                
                { // Lighting pass
                    StencilUse stencil;
                    
                    { // Ambient
                        shader::ProgramUse ambient(programs_.deferredAmbient_);
                        
                        BufferTextureUse tus(ambient, "uSampler", *buffer_, 2, 2);
                        lighting::AmbientLightUse(ambient, ambientLight);
                        
                        squareObj.render();
                    }
                    
                    glBlendFunc(GL_ONE, GL_ONE);
                    
                    { // Directional
                        shader::ProgramUse directional(programs_.deferredDir_);
                        
                        directional.setUniform("uEyePosition", cam.position());
                        
                        BufferTextureUse tu1(directional, "uSamplerPosition", *buffer_, 0, 0);
                        BufferTextureUse tu2(directional, "uSamplerNormal", *buffer_, 1, 1);
                        BufferTextureUse tu3(directional, "uSamplerColor", *buffer_, 2, 2);

                        for(const lighting::DirectionalLight& light : directionalLights) {
                            lighting::DirectionalLightUse use(directional, light);
                            
                            squareObj.render();
                        }
                    }
                    
                }
                
            }
            
            void DeferredRenderer::resize(int w, int h)
            {
                if (h * ratioWidth_ > w * ratioHeight_) {
                    int newWidth = h * ratioWidth_ / ratioHeight_;
                    viewport_ = {
                        -(newWidth - w) / 2, 0, newWidth, h
                    };
                } else {
                    int newHeight = w * ratioHeight_ / ratioWidth_;
                    viewport_ = {
                        0, -(newHeight - h) / 2, w, newHeight
                    };
                }
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