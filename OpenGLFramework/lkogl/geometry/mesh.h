//
//  mesh.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__mesh__
#define __OpenGLFramework__mesh__

#include <vector>

#include "../opengl.h"
#include "../math/math.h"

namespace lkogl {
    namespace geometry {
        
        typedef lkogl::math::Vec4<GLfloat> Color;
        typedef lkogl::math::Vec3<GLfloat> Vec3;
        typedef lkogl::math::Vec2<GLfloat> UVCoord;
        
        struct Vertex {
            Vec3 position;
            Vec3 normal;
            UVCoord textureCoord;
        };
        
        struct Triangle {
            GLuint a;
            GLuint b;
            GLuint c;
        };
        
        struct Mesh {
            std::vector<Vertex> vertices;
            std::vector<Triangle> triangles;
            
            Mesh(const std::vector<Vertex> vertices, const std::vector<Triangle> triangles);
        };
        
        namespace primitives {
            Mesh makeCube();
            Mesh makeSquare();
            Mesh makePyramid();
        }
    }
}

#endif /* defined(__OpenGLFramework__mesh__) */
