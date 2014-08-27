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
#include "../lighting/spot_light.h"
#include "../lighting/point_light.h"
#include "../lighting/directional_light.h"
#include "../lighting/ambient_light.h"
#include "../stencil.h"
#include "../../geometry/mesh.h"
#include "../../utils/image.h"
#include "../../resources/shader_loader/shader_loader.h"

#include <iostream>

using namespace lkogl::graphics::shader;

namespace lkogl {
    namespace graphics {
        namespace rendering {
            
            DeferredRenderer::DeferredRenderer(const Screen& s, int ratioWidth, int ratioHeight) throw (Shader::Exception) :
            programs_(initPrograms()), buffer_(new FrameBuffer(s.width, s.height, std::vector<TargetType> {
                TargetType{GL_COLOR_ATTACHMENT0, GL_RGBA16F},
                TargetType{GL_COLOR_ATTACHMENT1, GL_RGBA16F},
                TargetType{GL_COLOR_ATTACHMENT2, GL_RGBA16F},
            })), square_(geometry::primitives::makeSquare()), box_(geometry::primitives::makeCube()), ratioWidth_(ratioWidth), ratioHeight_(ratioHeight), sky_(utils::Image("sky.png"))
            {
            }
            
            DeferredRenderer::Programs DeferredRenderer::initPrograms() throw (Shader::Exception)
            {
                resources::shader_loader::ShaderLoader loader;
                
                Shader vshGeo = loader.fromFile(ShaderType::VERTEX, "deferred-geometry.vsh");
                
                Shader fshGeo = loader.fromFile(ShaderType::FRAGMENT, "deferred-geometry.fsh");
                
                
                
                Shader vshAmbient = loader.fromFile(ShaderType::VERTEX, "deferred-ambient.vsh");
                
                Shader fshAmbient = loader.fromFile(ShaderType::FRAGMENT, "deferred-ambient.fsh");
                
                
                
                Shader vshStencil = loader.fromFile(ShaderType::VERTEX, "deferred-stencil.vsh");
                
                Shader fshStencil = loader.fromFile(ShaderType::FRAGMENT, "deferred-stencil.fsh");
                
                
                
                Shader vshDir = loader.fromFile(ShaderType::VERTEX, "deferred-directional.vsh");
                
                Shader fshDir = loader.fromFile(ShaderType::FRAGMENT, "deferred-directional.fsh");
                
                
                Shader vshPoint = loader.fromFile(ShaderType::VERTEX, "deferred-point.vsh");
                
                Shader fshPoint = loader.fromFile(ShaderType::FRAGMENT, "deferred-point.fsh");
                
                
                Shader vshSpot = loader.fromFile(ShaderType::VERTEX, "deferred-spot.vsh");
                
                Shader fshSpot = loader.fromFile(ShaderType::FRAGMENT, "deferred-spot.fsh");
                
                
                
                Shader vshSky = loader.fromFile(ShaderType::VERTEX, "sky.vsh");
                
                Shader fshSky = loader.fromFile(ShaderType::FRAGMENT, "sky.fsh");
              
                
                return {
                    shader::Program(vshSky, fshSky),
                    shader::Program(vshGeo, fshGeo),
                    shader::Program(vshAmbient, fshAmbient),
                    shader::Program(vshStencil, fshStencil),
                    shader::Program(vshDir, fshDir),
                    shader::Program(vshPoint, fshPoint),
                    shader::Program(vshSpot, fshSpot)
                };
            }
            
            DeferredRenderer::~DeferredRenderer()
            {
            }
            
            void DeferredRenderer::render(const scene::Scene& graph, const camera::Camera& cam) const
            {
                std::vector<lighting::DirectionalLight> directionalLights = {
                    lighting::DirectionalLight({1,1,1}, 1.4, -math::Vec3<float>{1,2.6,0.4}),
                };
                
                std::vector<lighting::PointLight> pointLights = {
                    lighting::PointLight({1,0,0}, 1.4, {0,-1,0}, lighting::Attenuation(0,0,1)),
                    lighting::PointLight({0,1,0}, 1, {-9,-3.9,0}, lighting::Attenuation(0,1,0.8)),
                    lighting::PointLight({1,1,0}, 1, {-8.5,-2,-0.3}, lighting::Attenuation(0,0,1)),
                    lighting::PointLight({1,0,1}, 1, {-11,-4,-1.5}, lighting::Attenuation(0,1,0.8)),
                    lighting::PointLight({0,0.2,1}, 1, {-11,-2.6,0.9}, lighting::Attenuation(0,1,0.8)),
                    lighting::PointLight({1,0,1}, 1, {0,3.5,-2}, lighting::Attenuation(0,0,0.8)),
                    lighting::PointLight({1,1,1}, 0.5, {-10.5,-4,1.6}, lighting::Attenuation(0,0,1)),
                    lighting::PointLight({1,0.5,0}, 1, {-7.7,-2.8,1.5}, lighting::Attenuation(0,0,1)),
                };
                
                std::vector<lighting::SpotLight> spotLights = {
                    lighting::SpotLight({1,0,0}, 1, {-10,-2,2.3}, lighting::Attenuation(0,0.5,0.5), {0,-1,0}, 0.7),
                };
                
                lighting::AmbientLight ambientLight({0.2,0.2,0.2});
                
                math::geo::Frustum3<float> viewFrustum = math::geo::frustum_from_view_projection(cam.viewProjectionMatrix());
                
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
                    TextureUse t(skyProg, "uSkybox", sky_, 0);
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
                        
                        BufferTextureUse tu1(directional, "uGeometry.position", *buffer_, 0, 0);
                        BufferTextureUse tu2(directional, "uGeometry.normal", *buffer_, 1, 1);
                        BufferTextureUse tu3(directional, "uGeometry.color", *buffer_, 2, 2);
                        
                        for(const lighting::DirectionalLight& light : directionalLights) {
                            lighting::DirectionalLightUse use(directional, light);
                            
                            squareObj.render();
                        }
                    }
                    
                    { // Point
                        shader::ProgramUse point(programs_.deferredPoint_);
                        GeometryObjectUse squareObj(square_);
                        
                        point.setUniform("uEyePosition", cam.position());
                        
                        BufferTextureUse tu1(point, "uGeometry.position", *buffer_, 0, 0);
                        BufferTextureUse tu2(point, "uGeometry.normal", *buffer_, 1, 1);
                        BufferTextureUse tu3(point, "uGeometry.color", *buffer_, 2, 2);
                        
                        for(const lighting::PointLight& light : pointLights) {
                            if(math::geo::relationship(viewFrustum, light.boundingSphere()) != math::geo::VolumeRelation::OUTSIDE) {
                                lighting::PointLightUse use(point, light);
                                
                                squareObj.render();
                                entityCount_++;
                            }
                        }
                    }
                    
                    { // Spot
                        shader::ProgramUse spot(programs_.deferredSpot_);
                        GeometryObjectUse squareObj(square_);
                        
                        spot.setUniform("uEyePosition", cam.position());
                        
                        BufferTextureUse tu1(spot, "uGeometry.position", *buffer_, 0, 0);
                        BufferTextureUse tu2(spot, "uGeometry.normal", *buffer_, 1, 1);
                        BufferTextureUse tu3(spot, "uGeometry.color", *buffer_, 2, 2);
                        
                        for(const lighting::SpotLight& light : spotLights) {
                            if(math::geo::relationship(viewFrustum, light.boundingSphere()) != math::geo::VolumeRelation::OUTSIDE) {
                                lighting::SpotLightUse use(spot, light);
                                
                                squareObj.render();
                                auto a = light.boundingSphere();
                                entityCount_++;
                            }
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