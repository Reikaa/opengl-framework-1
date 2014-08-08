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
public:
    void setUp() const {
        std::cout << "setup" << std::endl;
        
        try {
            PlainText vshSource("phong.vsh");
            PlainText fshSource("phong.fsh");

            Program program(vshSource.content, fshSource.content);
            Mesh mesh = primitives::makeCube();
            GeometryObject geo(mesh);
            Material mat(program, {});
            Model modelOne(geo, mat);
            std::shared_ptr<Leaf> node = std::make_shared<Leaf>(modelOne);
        
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
        glClearColor(0,0.2,0.3,0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        graph.root().accept(r);
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
