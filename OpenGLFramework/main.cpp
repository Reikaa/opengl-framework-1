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
#include "lkogl/stencil.h"

#include "lkogl/element.h"
#include "lkogl/layout_renderer.h"
#include "lkogl/pointer_tracking.h"
#include "lkogl/layout_invalidator.h"
#include "lkogl/hover_behaviour.h"


#include "lkogl/ambient_light.h"
#include "lkogl/directional_light.h"
#include "lkogl/point_light.h"
#include "lkogl/spot_light.h"
#include "lkogl/deferred_renderer.h"

#include "lkogl/obj_model.h"
#include "lkogl/image_height_map.h"

#include "lkogl/animation_component.h"
#include "lkogl/camera_component.h"
#include "lkogl/render_component.h"
#include "lkogl/scene_deep_walker.h"

#include "lkogl/keyboard.h"
#include "lkogl/keyboard_adapter.h"
#include "lkogl/mouse.h"
#include "lkogl/mouse_adapter.h"

#include "lkogl/first_person_movement.h"

using namespace lkogl::ui;
using namespace lkogl::math;
using namespace lkogl::graphics;
using namespace lkogl::graphics::renderign;
using namespace lkogl::graphics::lighting;
using namespace lkogl::geometry;
using namespace lkogl::utils;
using namespace lkogl::resources::mesh_loader;
using namespace lkogl::scene;
using namespace lkogl::loop;
using namespace lkogl::math;
using namespace lkogl::scene::components;
using namespace lkogl::scene::walker;
using namespace lkogl::camera;
using namespace lkogl::input;
using namespace lkogl::input::movement;

class MyGame {
    
    mutable std::string extraTitle_;
    
    mutable std::shared_ptr<Node> graph;
    SceneDeepWalker walker;
    
    mutable std::shared_ptr<DeferredRenderer> renderer_;
    
    mutable std::shared_ptr<Node> camNode_;
    mutable std::shared_ptr<Node> monkeyNode_;
    mutable bool exprerimentToggle = false;

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

    LayoutInvalidator layoutInvalidator_;
    mutable std::shared_ptr<PointerTracking> pointerTracking_;
    mutable std::shared_ptr<Element> uiRoot_ = std::make_shared<Element>();
    mutable std::shared_ptr<LayoutRenderer> uiRenderer_;
    
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
        
        
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);
        glEnable(GL_CULL_FACE);
        
        glEnable( GL_DEPTH_TEST );
        glDepthFunc( GL_LEQUAL );
        
        
        glEnable(GL_DEPTH_CLAMP);
        
        try {
            
            renderer_ = std::make_shared<DeferredRenderer>(screen_, 16, 9);
            uiRenderer_ = std::make_shared<LayoutRenderer>();
            
            auto e1 = std::make_shared<Element>();
            auto e2 = std::make_shared<Element>(std::make_shared<behaviour::HoverBehaviour>());
            e2->layout().setSize(px(50), px(40));
            e1->layout().setMargin({percent(8)});
            e1->layout().setAlignment({WeightLinear::Center, WeightLinear::Center});
            e2->layout().setMargin({px(20)});
            e2->layout().setAlignment({WeightLinear::Right, WeightLinear::Bottom});
            
            uiRoot_->style().setBackground({0,0,0,0});
            
            uiRoot_->addChild(e1);
            e1->addChild(e2);
            
            pointerTracking_ = std::make_shared<PointerTracking>(uiRoot_);
            
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
            
            node->transformation.setRotation(angleAxis<float>(radians(1), {1,1,1}));
            graph->addChild(node);
            
            
            square_ = std::make_shared<GeometryObject>(primitives::makeSquare());
            
            Mesh cube = ::obj_from_file("box.obj").toIndexedModel().toMesh();
            std::shared_ptr<Node> node2 = std::make_shared<Node>();
            node2->addComponent(std::make_shared<RenderComponent>(GeometryObject(cube), mat));
            node2->transformation.setTranslation({-5,0.5,-2});
            node2->transformation.setRotation(angleAxis<float>(radians(45), {0,1,0}));
            node->addChild(node2);
            node2->transformation.setRotation(angleAxis<float>(radians(45), {0,1,0}));
            graph->addChild(node2);
            
            

            
            
            Mesh monkey = obj_from_file("monkey.obj").toIndexedModel().toMesh();
            std::shared_ptr<Node> node3 = std::make_shared<Node>();
            node3->addComponent(std::make_shared<RenderComponent>(GeometryObject(monkey), mat));
            Transformation spin;
            spin.rotation = angleAxis(radians(1.0f), {0.0f,1.0f,0.0f});;
            
            node3->addComponent(std::make_shared<AnimationComponent>(spin));
            node3->transformation.setTranslation({5,1,-2});
            node3->transformation.setRotation(angleAxis<float>(radians(45), {0.1,1,0.3}));
            node->addChild(node3);
            
            
            
            Image terrainImage("terrain.png");
            ImageHeightMap terrainMap = heigh_map_from_image(terrainImage);
            Mesh terrainMesh = terrainMap.toIndexedModel().toMesh();
            
            std::shared_ptr<Node> node4 = std::make_shared<Node>();
            node4->addComponent(std::make_shared<RenderComponent>(GeometryObject(terrainMesh), mat));
            graph->addChild(node4);


            
            movement.setFly(true);
            
            cameraComponent = std::make_shared<CameraComponent>(Camera(screen_.width, screen_.height));
            
            camNode_ = std::make_shared<Node>();

            camNode_->addComponent(cameraComponent);
            camNode_->transformation.setTranslation({-4,1,-6});
            graph->addChild(camNode_);
            monkeyNode_ = node3;
            
            movement.lookAt(camNode_->transformation, {0,0,0});

            
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
                camNode_->transformation.setTranslation({camNode_->transformation.translation().x, 0, camNode_->transformation.translation().z});
                movement.setFly(false);
            } else {
                movement.setFly(true);
            }
        }
        
        if(mouseLocked) {
            movement.move(camNode_->transformation, dir, moveDelay/2);
            
            if(keyboard_.isDown(Keyboard::Key::LETTER_C)) {
                movement.lookAt(camNode_->transformation, {0,0,0});
            } else {
                if(mouse_.delta.x != 0) {
                    movement.rotateHorizontally(camNode_->transformation, radians(.25f*mouse_.delta.x));
                }
                if(mouse_.delta.y != 0) {
                    movement.rotateVertically(camNode_->transformation, radians(.25f*mouse_.delta.y));
                }
            }
        }
        
        if(keyboard_.pressed(Keyboard::Key::LETTER_T)) {
            if(exprerimentToggle) {
                monkeyNode_->removeChild(camNode_);
                graph->addChild(camNode_);
            } else {
                graph->removeChild(camNode_);
                monkeyNode_->addChild(camNode_);
            }
            exprerimentToggle = !exprerimentToggle;
        }
        

        if(!mouseLocked) {
            pointerTracking_->track(mouse_.position);
            if(mouse_.pressed(Mouse::Button::LEFT))
            {
                pointerTracking_->beginPointing(mouse_.position);
            }
            
            if(mouse_.released(Mouse::Button::LEFT))
            {
                pointerTracking_->endPointing(mouse_.position);
            }
        }
    }
    
    void update() const {
        keyboard_.update();
        mouse_.update();
        
        walker.walk(graph, &Component::update);
    }
    
    void render() const {
        renderer_->render(graph, cameraComponent->camera());
        
        if(!mouseLocked) {
            uiRenderer_->render(uiRoot_, screen_);
        }
    }
    
    void resize(int width, int height) const {
        screen_.width = width;
        screen_.height = height;
        
        if(renderer_.get() != 0) {
            renderer_->resize(width, height);
        }
        
        uiRoot_->layout().setWidth(width);
        uiRoot_->layout().setHeight(height);
        
        layoutInvalidator_.invalidate(uiRoot_);
    }
    
    const std::string title() const {
        std::stringstream ss;
        ss
        << "My Game"
        << " (" << "OpenGL " << glGetString(GL_VERSION) << ")"
        << " " << extraTitle_;
        
        return ss.str();
    }
    
    void report(int frameCount, int updateCount, long frameTimeAvg) const {
        std::ostringstream ss;
        
        ss << "f: " << frameCount << "/s, "
        << "u: " << updateCount << "/s, "
        << "rt: ~" << updateCount/1000.0 << "ms"
        ;
        
        extraTitle_ = ss.str();
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
