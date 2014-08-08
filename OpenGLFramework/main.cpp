//
//  main.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include <iostream>
#include "lkogl/game_loop.h"
#include "lkogl/scene_renderer.h"
#include "lkogl/graph.h"
#include "lkogl/material.h"
#include "lkogl/shader.h"
#include "lkogl/text.h"

using namespace lkogl::graphics;
using namespace lkogl::geometry;
using namespace lkogl::utils;
using namespace lkogl::scene;
using namespace lkogl::loop;

class MyGame {
    visitor::SceneRenderer r;
    SceneGraph graph;
    mutable struct {
        int width, height;
    } screen;
public:
    void setUp() const {
        std::cout << "setup" << std::endl;
        
        /* Enable smooth shading */
        //glShadeModel( GL_SMOOTH );
        
        /* Set the background black */
        glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
        
        /* Depth buffer setup */
        glClearDepth( 1.0f );
        
        glEnable(GL_TEXTURE_2D);
        
        //glEnable(GL_CULL_FACE);
        glEnable( GL_BLEND );
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        /* Enables Depth Testing */
        glEnable( GL_DEPTH_TEST );
        /* The Type Of Depth Test To Do */
        glDepthFunc( GL_LEQUAL );
        
        
        /* Really Nice Perspective Calculations */
        //glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
        
        try {
            PlainText vshSource("phong.vsh");
            PlainText fshSource("phong.fsh");

            Program program(vshSource.content, fshSource.content);
            Mesh mesh = primitives::makePyramid();
            GeometryObject geo(mesh);
            Material mat(std::move(program), {});
            Model modelOne(std::move(geo), std::move(mat));
            std::shared_ptr<Leaf> node = std::make_shared<Leaf>(std::move(modelOne));
        
            
            graph.root().add(node);
        } catch(ShaderException e) {
            std::cerr << e.msg << std::endl;
            exit(1);
        }
    }
    
    void tearDown() const {
        std::cout << "tear down" << std::endl;
    }
    
    void input() const {
    
    }
    
    void update() const {
    
    }
    
    void render() const {
        adjustViewport();
        
        glClearColor(0,0.2,0.3,0);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        
        graph.root().accept(r);
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
        return "My Game";
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
