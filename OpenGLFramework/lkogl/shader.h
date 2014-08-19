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
#include <map>
#include <set>
#include <exception>

#include "variable_declaration.h"
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
        
        class Shader {
            mutable GLuint handle_;
            mutable struct Variables {
                std::vector<VariableDeclaration> uniforms;
                std::vector<VariableDeclaration> input;
                std::vector<VariableDeclaration> output;
            } variables_;
        public:
            Shader(ShaderType, const std::string&) throw (ShaderException);
            Shader(const Shader&&) throw ();

            ~Shader();
            const GLuint& handle() const { return handle_; }
            const std::vector<VariableDeclaration>& uniforms() const { return variables_.uniforms; }
            const std::vector<VariableDeclaration>& inputs() const { return variables_.input; }
            const std::vector<VariableDeclaration>& outputs() const { return variables_.output; }
        private:
            struct VariableDefinition {
                std::string type;
                std::string name;
            };
            
            GLuint compile(ShaderType, const std::string&) throw (ShaderException);
            
            typedef std::multimap<std::string, VariableDefinition> StructMap;
            Variables extractVariables(const std::string& source) const;
            std::vector<VariableDeclaration> extractDeclaration(const std::string& source, const std::string& keyword, const StructMap& structs) const;
            StructMap extractStructs(const std::string& source) const;
        };
        
        
    }
}

#endif /* defined(__OpenGLFramework__shader__) */
