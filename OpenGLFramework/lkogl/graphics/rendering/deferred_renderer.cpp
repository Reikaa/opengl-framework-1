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
#include "../stencil.h"
#include "../../geometry/mesh.h"
#include "../../utils/image.h"

#include <iostream>

namespace lkogl {
    namespace graphics {
        namespace rendering {
            
            DeferredRenderer::DeferredRenderer(const Screen& s, int ratioWidth, int ratioHeight) :
            programs_(initPrograms()), buffer_(new FrameBuffer(s.width, s.height, std::vector<TargetType> {
                TargetType{GL_COLOR_ATTACHMENT0, GL_RGBA16F},
                TargetType{GL_COLOR_ATTACHMENT1, GL_RGBA16F},
                TargetType{GL_COLOR_ATTACHMENT2, GL_RGBA16F},
            })), square_(geometry::primitives::makeSquare()), box_(geometry::primitives::makeCube()), ratioWidth_(ratioWidth), ratioHeight_(ratioHeight), sky_(utils::Image("sky.png"))
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
                
                utils::PlainText vshDefSky("sky.vsh");
                utils::PlainText fshDefSky("sky.fsh");
                
                return {
                    shader::Program(vshDefSky.content, fshDefSky.content),
                    shader::Program(vshDefGeo.content, fshDefGeo.content),
                    shader::Program(vshDefPlain.content, fshDefPlain.content),
                    shader::Program(vshDefStencil.content, fshDefStencil.content),
                    shader::Program(vshDefDir.content, fshDefDir.content)
                };
            }
            
            DeferredRenderer::~DeferredRenderer()
            {
            }
            
            void DeferredRenderer::render(const scene::Scene& graph, const camera::Camera& cam) const
            {
                std::vector<lighting::DirectionalLight> directionalLights = {
                    lighting::DirectionalLight({1,1,1}, 1.4, -math::Vec3<float>{1,2.6,0.4}),
                    lighting::DirectionalLight({1,1,1}, 0.2, math::Vec3<float>{2,-1,-2}),
                    lighting::DirectionalLight({1,1,1}, 0.2, math::Vec3<float>{-1,-1,3}),
                };
                
                lighting::AmbientLight ambientLight({0.2,0.2,0.2});
            
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
                    
                    math::geo::Frustum3<float> viewFrustum = math::geo::frustum_from_view_projection(cam.viewProjectionMatrix());
                    
                    auto entities = graph.query([viewFrustum](const scene::Entity& e) {
                        auto box = math::geo::transformed(e.bounding(), e.transformation().matrix());
                        return math::geo::relationship(viewFrustum, box) != math::geo::VolumeRelation::OUTSIDE;
                    });
                    
                    entityCount_ = (int)entities.size();
                    
                    for(auto e : entities) {
                        for(auto c : e->components()) {
                            c->render(*e.get(), defgeo);
                        }
                        
//                        auto box = math::geo::transform(e->bounding(), e->transformation().matrix());
//
//                        for(auto c : box.corners()) {
//                            defgeo.setUniform("uModelMatrix", math::translate(math::scale(math::Mat4<float>(1), 0.02f), c));
//                            defgeo.setUniform("uMaterial.coloring", math::Vec4<float>(0.9,0,0,1));
//                            const graphics::GeometryObjectUse geo(box_);
//                            geo.render();
//                        }
                    }
                    //walker.walk(graph, &scene::components::Component::render, defgeo);
                    
                    glDepthMask(GL_FALSE);
                    glDisable(GL_DEPTH_TEST);
                }
                
                MainTargetUse s;
                glViewport(0, 0, screen_.width, screen_.height);
                Stencil stencil;
                
                {
                    

                    shader::ProgramUse stencilProg(programs_.deferredStencil_);
                    GeometryObjectUse squareObj(square_);

                    BufferTextureUse tus(stencilProg, "uSampler", *buffer_, 0, 0);
                    
                    squareObj.render();
                }
                
                //Skybox
                {
                    stencil.filter(0);
                    glCullFace(GL_FRONT);
                    GeometryObjectUse box(box_);
                    shader::ProgramUse skyProg(programs_.skybox_);
                    TextureUse t(skyProg, sky_, 0);
                    skyProg.setUniform("uViewProjMatrix", cam.viewProjectionMatrix());
                    skyProg.setUniform("uModelMatrix", math::scale(math::translate(math::Mat4<float>(1), cam.position()), 100.0f));
                    box.render();
                    glCullFace(GL_BACK);
                }
                
                
                
                { // Lighting pass
                    stencil.filter(1);
                    
                    { // Ambient
                        shader::ProgramUse ambient(programs_.deferredAmbient_);
                        GeometryObjectUse squareObj(square_);

                        BufferTextureUse tus(ambient, "uSampler", *buffer_, 2, 2);
                        lighting::AmbientLightUse(ambient, ambientLight);
                        
                        squareObj.render();
                    }
                    glEnable(GL_BLEND);
                    glBlendEquation(GL_FUNC_ADD);
                    glBlendFunc(GL_ONE, GL_ONE);
                    
                    { // Directional
                        shader::ProgramUse directional(programs_.deferredDir_);
                        GeometryObjectUse squareObj(square_);

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