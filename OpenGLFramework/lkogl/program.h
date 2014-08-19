//
//  program.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 11.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__program__
#define __OpenGLFramework__program__

#include <map>

#include "shader.h"
#include "variable_declaration.h"

namespace lkogl {
    namespace graphics {
        namespace shader {
            class Program {
                struct ProgramHandles {
                    mutable GLuint programId;
                    std::map<VariableDeclaration, GLuint> uniforms;
                    std::map<VariableDeclaration, GLuint> inputs;
                } handles_;
            public:
                class Exception {
                public:
                    Exception(const std::string& msg) {}
                    Exception() {}
                };
                
                Program(const std::string& vsh, const std::string& fsh) throw (Exception);
                Program(const Shader& vsh, const Shader& fsh) throw (Exception);
                Program(const Program&&) throw();
                ~Program();
                
                const ProgramHandles& handles() const { return handles_; }
                const GLuint uniformLocation(const VariableDeclaration& u) const;
            private:
                ProgramHandles link(const Shader& vsh, const Shader& fsh) throw (Exception);
                
            };
            
            class ProgramUse {
                const Program& program_;
            public:
                explicit ProgramUse(const Program&);
                
                void setUniformf(const std::string& name, GLfloat value) const;
                void setUniformi(const std::string& name, GLuint value) const;
                void setUniform(const std::string& name, const math::Vec2<GLfloat>& value) const;
                void setUniform(const std::string& name, const math::Vec3<GLfloat>& value) const;
                void setUniform(const std::string& name, const math::Vec4<GLfloat>& value) const;
                void setUniform(const std::string& name, const math::Mat4<GLfloat>& value) const;
                
                ~ProgramUse();
            };
        }
    }
}

#endif /* defined(__OpenGLFramework__program__) */
