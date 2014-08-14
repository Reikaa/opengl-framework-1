//
//  main.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include <iostream>
#include <sstream>
#include "lkogl/game_loop.h"
#include "lkogl/material.h"
#include "lkogl/shader.h"
#include "lkogl/text.h"
#include "lkogl/render_target.h"

#include "lkogl/ambient_light.h"
#include "lkogl/ambient_light_component.h"
#include "lkogl/directional_light.h"
#include "lkogl/point_light.h"
#include "lkogl/spot_light.h"


#include "lkogl/obj_model.h"


#include "lkogl/animation_component.h"
#include "lkogl/camera_component.h"
#include "lkogl/render_component.h"
#include "lkogl/scene_deep_walker.h"

#include "lkogl/keyboard.h"
#include "lkogl/keyboard_adapter.h"
#include "lkogl/mouse.h"
#include "lkogl/mouse_adapter.h"

#include "lkogl/first_person_movement.h"

using namespace lkogl::math;
using namespace lkogl::graphics;
using namespace lkogl::graphics::lighting;
using namespace lkogl::geometry;
using namespace lkogl::utils;
using namespace lkogl::scene;
using namespace lkogl::loop;
using namespace lkogl::math;
using namespace lkogl::scene::components;
using namespace lkogl::scene::walker;
using namespace lkogl::camera;
using namespace lkogl::input;
using namespace lkogl::input::movement;

class MyGame {
    mutable std::shared_ptr<Node> graph;
    SceneDeepWalker walker;
    
    mutable std::shared_ptr<Texture> deferredTexture_;
    
    mutable std::shared_ptr<Program> programAmbient_;
    mutable std::shared_ptr<Program> programDirectional_;
    mutable std::shared_ptr<Program> programPoint_;
    mutable std::shared_ptr<Program> programSpot_;
    mutable std::shared_ptr<Program> programDeferredGeo_;
    mutable std::shared_ptr<Program> programDeferredPlain_;
    mutable std::shared_ptr<Program> programDeferredDir_;

    mutable std::shared_ptr<CameraComponent> cameraComponent;
    
    mutable std::shared_ptr<GeometryObject> square_;
    mutable std::shared_ptr<Texture> texture_;
    
    mutable FirstPersonMovement movement;
    mutable float moveDelay = 0.f;
    
    mutable Keyboard keyboard_;
    adapter::KeyboardAdapter kbAdapter_;
    
    mutable Mouse mouse_;
    adapter::MouseAdapter mouseAdapter_;
    
    mutable Screen screen_;
    
public:
    mutable bool mouseLocked = true;
    
    MyGame() : kbAdapter_(keyboard_), mouseAdapter_(mouse_)
    {}
    
    void setUp() const {
        std::cout << "setup" << std::endl;
        
        glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
        glClearDepth( 1.0f );
        
        glEnable(GL_TEXTURE_2D);
        glEnable( GL_BLEND );
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);
        glEnable(GL_CULL_FACE);
        
        glEnable( GL_DEPTH_TEST );
        glDepthFunc( GL_LEQUAL );
        
        
        glEnable(GL_DEPTH_CLAMP);
        
        try {
            
            PlainText vshSourceAmbient("ambient-forward.vsh");
            PlainText fshSourceAmbient("ambient-forward.fsh");
            programAmbient_ = std::make_shared<Program>(vshSourceAmbient.content, fshSourceAmbient.content);
            
            PlainText vshSourceDirectional("directional-forward.vsh");
            PlainText fshSourceDirectional("directional-forward.fsh");
            programDirectional_ = std::make_shared<Program>(vshSourceDirectional.content, fshSourceDirectional.content);
            
            PlainText vshSourcePoint("point-forward.vsh");
            PlainText fshSourcePoint("point-forward.fsh");
            programPoint_ = std::make_shared<Program>(vshSourcePoint.content, fshSourcePoint.content);
            
            PlainText vshSourceSpot("spot-forward.vsh");
            PlainText fshSourceSpot("spot-forward.fsh");
            programSpot_ = std::make_shared<Program>(vshSourceSpot.content, fshSourceSpot.content);
            
            PlainText vshDefGeo("deferred-geometry.vsh");
            PlainText fshDefGeo("deferred-geometry.fsh");
            programDeferredGeo_ = std::make_shared<Program>(vshDefGeo.content, fshDefGeo.content);
            
            PlainText vshDefPlain("deferred-plain.vsh");
            PlainText fshDefPlain("deferred-plain.fsh");
            programDeferredPlain_ = std::make_shared<Program>(vshDefPlain.content, fshDefPlain.content);
            
            PlainText vshDefDir("deferred-directional.vsh");
            PlainText fshDefDir("deferred-directional.fsh");
            programDeferredDir_ = std::make_shared<Program>(vshDefDir.content, fshDefDir.content);
            
            graph = std::make_shared<Node>();
            
            texture_ = std::make_shared<Texture>(Image("pattern.png"));
            
            Texture tex(Image("pattern.png"));
            Material mat(tex, 7, 20);
            
            Texture tex2(Image("plain.png"));
            Material mat2(tex2, 7, 20);
            
            Mesh pyramid = primitives::makePyramid();
            std::shared_ptr<Node> node = std::make_shared<Node>();
            node->addComponent(std::make_shared<RenderComponent>(GeometryObject(pyramid), mat));
            node->transformation.setTranslation({0,1,0});
            
            node->transformation.setRotation(angleAxis<float>(radians(1.0), {1,1,1}));
            graph->addChild(node);
            
            
            square_ = std::make_shared<GeometryObject>(primitives::makeSquare());
            
            Mesh cube = lkogl::resources::mesh_loader::obj_from_file("box.obj").toIndexedModel().toMesh();
            std::shared_ptr<Node> node2 = std::make_shared<Node>();
            node2->addComponent(std::make_shared<RenderComponent>(GeometryObject(cube), mat));
            node2->transformation.setTranslation({-5,0.5,-2});
            node2->transformation.setRotation(angleAxis<float>(radians(45), {0,1,0}));
            node->addChild(node2);
            
            Mesh monkey = lkogl::resources::mesh_loader::obj_from_file("monkey.obj").toIndexedModel().toMesh();
            std::shared_ptr<Node> node3 = std::make_shared<Node>();
            node3->addComponent(std::make_shared<RenderComponent>(GeometryObject(monkey), mat));
            Transformation spin;
            spin.rotation = angleAxis(radians(1.0f), {0.0f,1.0f,0.0f});;
            
            node3->addComponent(std::make_shared<AnimationComponent>(spin));
            node3->transformation.setTranslation({5,1,-2});
            node3->transformation.setRotation(angleAxis<float>(radians(45), {0,1,0}));
            node->addChild(node3);
            
            
            movement.setFly(true);
            
            auto cam = Camera(screen_.width, screen_.height);
            cam.setPosition({4,1,5});
            movement.lookAt(cam, {0,0,0});
            cameraComponent = std::make_shared<CameraComponent>(cam);
            
            graph->addComponent(cameraComponent);
            graph->addComponent(std::make_shared<AmbientLightComponent>(AmbientLight({0.1,0.1,0.1})));
            
        } catch(ShaderException e) {
            std::cerr << e.msg << std::endl;
            exit(1);
        }
    }
    
    void tearDown() const {
        std::cout << "tear down" << std::endl;
    }
    
    void processEvent(const SDL_Event& e) const {
        kbAdapter_.processEvent(e) || mouseAdapter_.processEvent(e);
    }
    
    void input() const {
        Vec2<float> dir(0,0);
        
        if(keyboard_.pressed(Keyboard::Key::ESCAPE)) {
            mouseLocked = !mouseLocked;
        }
        
        if(keyboard_.isDown(Keyboard::Key::LEFT_ARROW) || keyboard_.isDown(Keyboard::Key::LETTER_A)) {
            dir.x+=1;
        }
        if(keyboard_.isDown(Keyboard::Key::RIGHT_ARROW) || keyboard_.isDown(Keyboard::Key::LETTER_D)) {
            dir.x-=1;
        }
        
        if(keyboard_.isDown(Keyboard::Key::UP_ARROW) || keyboard_.isDown(Keyboard::Key::LETTER_W)) {
            dir.y+=1;
        }
        if(keyboard_.isDown(Keyboard::Key::DOWN_ARROW) || keyboard_.isDown(Keyboard::Key::LETTER_S)) {
            dir.y-=1;
        }
        
        if(length(dir)) {
            if(moveDelay<0.25) {
                moveDelay+=0.03125;
            }
        } else if(moveDelay>0) {
            moveDelay-=0.03125;
        }
        
        if(keyboard_.pressed(Keyboard::Key::LETTER_F)) {
            if(movement.canFly()) {
                cameraComponent->camera().setPosition({cameraComponent->camera().position().x,1,cameraComponent->camera().position().z});
                movement.setFly(false);
            } else {
                movement.setFly(true);
            }
        }
        
        if(mouseLocked) {
            movement.move(cameraComponent->camera(), dir, moveDelay/2);
            
            if(keyboard_.isDown(Keyboard::Key::LETTER_C)) {
                movement.lookAt(cameraComponent->camera(), {0,0,0});
            } else {
                if(mouse_.delta.x != 0) {
                    movement.rotateHorizontally(cameraComponent->camera(), radians(.25f*mouse_.delta.x));
                }
                if(mouse_.delta.y != 0) {
                    movement.rotateVertically(cameraComponent->camera(), radians(.25f*mouse_.delta.y));
                }
            }
        }
        
    }
    
    void update() const {
        keyboard_.update();
        mouse_.update();
        
        walker.walk(graph, &Component::update);
    }
    
    void render() const {
        {

            TextureRendering tr(*deferredTexture_);
            //glEnable( GL_BLEND );


            glClearColor(0,0,0,0);


            glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
            
            ProgramUse defgeo(*programDeferredGeo_);
            walker.walk(graph, &Component::render, *programDeferredGeo_);
            //glDisable( GL_BLEND );

        }
        
        DirectionalLight light({0.6,0.7,0.9}, 0.1, {1,-1,1});
        DirectionalLight light2({0.6,0.7,0.9}, 0.1, {-1,-1,-1});

        
        {
            ScreenRendering s(screen_, 16, 9);

            glClearColor(1,1,1,1);
            glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
            ProgramUse plain(*programDeferredDir_);
            glUniform3f(programDeferredDir_->handles().eyePosition, cameraComponent->camera().position().x, cameraComponent->camera().position().y, cameraComponent->camera().position().z);

            TextureUse tu1(programDeferredDir_->handles().samplerPosPosition, *deferredTexture_, 0, 0);
            
            TextureUse tu2(programDeferredDir_->handles().samplerNormPosition, *deferredTexture_, 1, 1);
                           
            TextureUse tu3(programDeferredDir_->handles().samplerColPosition, *deferredTexture_, 2, 2);
            
            GeometryObjectUse gu(*square_);
            
            DirectionalLightUse lightuse(*programDeferredDir_, light);
            
            gu.render();
            
            DirectionalLightUse lightuse2(*programDeferredDir_, light2);
            
            gu.render();
        }
        
        if(keyboard_.isDown(Keyboard::Key::SPACE)){
            ScreenRendering(screen_, 16, 9);
            glClearColor(0,0,0,0);
            glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
            ProgramUse directional(*programDirectional_);
            
            DirectionalLightUse lightuse(*programDirectional_, light);

            walker.walk(graph, &Component::render, *programDirectional_);

            DirectionalLightUse lightuse2(*programDirectional_, light2);
            
            walker.walk(graph, &Component::render, *programDirectional_);

        }
        
//        glEnable( GL_POLYGON_OFFSET_FILL );
//        glPolygonOffset( -.1f, -0.1f );
//        glEnable(GL_BLEND);
//        glBlendFunc(GL_ONE, GL_ONE);
//        
//        glDepthFunc(GL_LEQUAL);
        
//        {
//            ProgramUse directional(*programDirectional_);
//            DirectionalLight light({0.6,0.7,0.9}, 0.1, {1,-1,1});
//            DirectionalLightUse lightuse(*programDirectional_, light);
//            
//            walker.walk(graph, &Component::render, *programDirectional_);
//            
//            DirectionalLight light2({0.6,0.7,0.9}, 0.1, {-1,-1,-1});
//            DirectionalLightUse lightuse2(*programDirectional_, light2);
//            
//            walker.walk(graph, &Component::render, *programDirectional_);
//        }
        
//        
//        glPolygonOffset( -.2f, -0.2f );
//        
//        {
//            ProgramUse pointy(*programPoint_);
//            PointLight pp({1,0,0}, 0.7, {0,2,2}, Attenuation(0, 0, 1));
//            PointLightUse(*programPoint_, pp);
//            
//            walker.walk(graph, &Component::render, *programPoint_);
//            
            //            PointLight pp2({1,0,1}, 0.7, {0,2,-2}, Attenuation(0, 0, 1));
            //            PointLightUse(*programPoint_, pp2);
            //
            //            walker.walk(graph, &Component::render, *programPoint_);
            
            //
            //            PointLight pp3({0,1,1}, 0.7, {-2,2,0}, Attenuation(0, 0, 1));
            //            PointLightUse(*programPoint_, pp3);
            //
            //            walker.walk(graph, &Component::render, *programPoint_);
            //
            //            PointLight pp4({1,1,0}, 0.7, {2,2,0}, Attenuation(0, 0, 1));
            //            PointLightUse(*programPoint_, pp4);
            //
            //            walker.walk(graph, &Component::render, *programPoint_);
//        }
//
//        glPolygonOffset( -.3f, -0.3f );
//        
//        {
//            ProgramUse spoty(*programSpot_);
//            SpotLight sp({1,1,0}, 0.7, {-3.9,2,-2}, Attenuation(1, 0, 4), {.1,-1,0}, 0.5);
//            SpotLightUse(*programSpot_, sp);
//            
//            walker.walk(graph, &Component::render, *programSpot_);
//        }
//        
//        glDisable( GL_POLYGON_OFFSET_FILL );
//        
//        glDepthFunc(GL_LEQUAL);
//        
//        glDepthMask(GL_TRUE);
//        glDisable(GL_BLEND);
    }
    
    void resize(int width, int height) const {
        screen_.width = width;
        screen_.height = height;
        
        deferredTexture_ = std::make_shared<Texture>(screen_.width,screen_.height, std::vector<GLenum>{GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2});
    }
    
    const std::string title() const {
        std::stringstream ss;
        ss << "My Game" << "  (" << "OpenGL " << glGetString(GL_VERSION) << ")";
        
        return ss.str();
    }
    
    void report(int frameCount, int updateCount) const {
        std::cout << "fps:" << frameCount << ", ups: " << updateCount << std::endl;
    }
    
    ~MyGame() {
        
    }
};

int main(int argc, const char * argv[]) {
    const MyGame game = MyGame();
    const Loop<MyGame> l(game);
    
    l.start();
    
    return 0;
}
