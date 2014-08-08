//
//  shader.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__shader__
#define __OpenGLFramework__shader__

#include <stdio.h>
#include <string>
#include <exception>

#include "opengl.h"
#include "mesh.h"

namespace lkogl {
    namespace graphics {
        class ShaderException : std::exception {
            public:
            const std::string msg;

            ShaderException(const std::string& m);
            ~ShaderException();
        };
        
        enum class ShaderType {
            VERTEX = GL_VERTEX_SHADER,
            FRAGMENT = GL_FRAGMENT_SHADER
        };
        
        enum PointerLocation {
            LOCATION_POSITION,
            LOCATION_NORMAL,
            LOCATION_COLOR,
            LOCATION_TEXTURE_COORDS
        };
        
        class Shader {
            GLuint handle_;
        public:
            Shader(ShaderType, const std::string&) throw (ShaderException);
            Shader(Shader&&) throw ();

            ~Shader();
            const GLuint& handle() const { return handle_; }

        private:
            GLuint compile(ShaderType, const std::string&) throw (ShaderException);
        };
        
        class Program {
            GLuint handle_;

        public:
            Program(const std::string& vsh, const std::string& fsh) throw (ShaderException);
            Program(const Shader& vsh, const Shader& fsh) throw (ShaderException);
            Program(Program&&) throw();
            ~Program();
            
            const GLuint& handle() const { return handle_; }
        private:
            GLuint link(const Shader& vsh, const Shader& fsh) throw (ShaderException);

        };
        
        class ProgramUse {
            const Program& program_;
        public:
            ProgramUse(const Program&);
            ~ProgramUse();
        };
        
        class GeometryObject {
            struct GeometryHandle {
                GLuint object;
                GLuint vertexBuffer;
                GLuint indexBuffer;
            } handles_;
            int indexCount_;
            
        public:
            
            GeometryObject(const geometry::Mesh&);
            GeometryObject(GeometryObject&&);
            ~GeometryObject();
            
            const GeometryHandle& handle() const { return handles_; }
            const int& indexCount() const { return indexCount_; }
        private:
            GeometryHandle buffer(const geometry::Mesh& mesh);
        };
        
        class GeometryObjectUse {
            const GeometryObject& geometry_;
            public:
            GeometryObjectUse(const GeometryObject&);
            ~GeometryObjectUse();
            
            void render();
        };
    }
}

#endif /* defined(__OpenGLFramework__shader__) */
