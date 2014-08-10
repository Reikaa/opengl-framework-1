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

#include "lkogl/ambient_light.h"
#include "lkogl/ambient_light_component.h"
#include "lkogl/directional_light.h"


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
    mutable std::shared_ptr<Program> programAmbient_;
    mutable std::shared_ptr<Program> programDirectional_;
    mutable std::shared_ptr<CameraComponent> cameraComponent;
    
    FirstPersonMovement movement;
    mutable float moveDelay = 0.f;
    
    mutable Keyboard keyboard_;
    adapter::KeyboardAdapter kbAdapter_;
    
    mutable Mouse mouse_;
    adapter::MouseAdapter mouseAdapter_;
    
    mutable struct {
        int width, height;
    } screen;
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
        
        glEnable(GL_FRAMEBUFFER_SRGB);
        
        glEnable(GL_DEPTH_CLAMP);

        
        try {
            PlainText vshSourceAmbient("ambient-forward.vsh");
            PlainText fshSourceAmbient("ambient-forward.fsh");
            programAmbient_ = std::make_shared<Program>(vshSourceAmbient.content, fshSourceAmbient.content);
            
            PlainText vshSourceDirectional("directional-forward.vsh");
            PlainText fshSourceDirectional("directional-forward.fsh");
            programDirectional_ = std::make_shared<Program>(vshSourceDirectional.content, fshSourceDirectional.content);
            
            graph = std::make_shared<Node>();

            Mesh mesh = primitives::makePyramid();
            GeometryObject geo(mesh);
            Texture tex(Image("pattern.png"));
            Material mat(std::move(tex), 7, 20);
            Model modelOne(std::move(geo), std::move(mat));
            std::shared_ptr<Node> node = std::make_shared<Node>();
            node->addComponent(std::make_shared<RenderComponent>(std::move(modelOne)));
            node->transformation.translation = Vec3<GLfloat>(0,0.0001,0);
            node->transformation.rotation = angleAxis<float>(radians(45), {0,1,0});
            
            graph->addChild(node);
            auto cam = Camera(screen.width, screen.height);
            cam.setPosition({4,1,5});
            cam.lookAt({0,0,0});
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
        
        movement.move(cameraComponent->camera(), dir, moveDelay/2);
                
        if(mouseLocked) {
            if(mouse_.delta.x != 0) {
                movement.rotateHorizontally(cameraComponent->camera(), radians(.25f*mouse_.delta.x));
            }
            if(mouse_.delta.y != 0) {
                movement.rotateVertically(cameraComponent->camera(), radians(.25f*mouse_.delta.y));
            }
        }
        
    }
    
    void update() const {
        keyboard_.update();
        mouse_.update();
    }
    
    void render() const {
        adjustViewport();
        
        glClearColor(0,0.2,0.3,0);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        ProgramUse ambient(*programAmbient_);
        walker.walk(graph, &Component::render, *programAmbient_);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);
        glDepthMask(false);
        glDepthFunc(GL_EQUAL);
        
        ProgramUse directional(*programDirectional_);
        DirectionalLight light;
        light.direction_ = {0,-1,0};
        light.baseLight_.color_ = {0.6,0.7,0.9};
        light.baseLight_.intensity_ = 0.9;
        DirectionalLightUse lightuse(*programDirectional_, light);
        
        walker.walk(graph, &Component::render, *programDirectional_);
        
        
        glDepthFunc(GL_LEQUAL);
        glDepthMask(true);
        glDisable(GL_BLEND);
    }
    
    void resize(int width, int height) const {
        screen.width = width;
        screen.height = height;
    }
    
    void adjustViewport() const {
        if (screen.height * 16 > screen.width * 9) {
            int newWidth = screen.height * 16 / 9;
            glViewport(-(newWidth - screen.width) / 2, 0, newWidth,
                       screen.height);
        } else {
            int newHeight = screen.width * 9 / 16;
            glViewport(0, -(newHeight - screen.height) / 2,
                       screen.width, newHeight);
        }
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
