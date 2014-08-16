//
//  shader.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__shader__
#define __OpenGLFramework__shader__

#include <string>
#include <exception>

#include "mesh.h"
#include "math.h"

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
            mutable GLuint handle_;
        public:
            Shader(ShaderType, const std::string&) throw (ShaderException);
            Shader(const Shader&&) throw ();

            ~Shader();
            const GLuint& handle() const { return handle_; }

        private:
            GLuint compile(ShaderType, const std::string&) throw (ShaderException);
        };
        
        
    }
}

#endif /* defined(__OpenGLFramework__shader__) */
