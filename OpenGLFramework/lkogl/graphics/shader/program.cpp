//
//  program.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 11.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./program.h"
#include <iostream>

namespace lkogl {
    namespace graphics {
        namespace shader {
            Program::Program(const Shader& vsh, const Shader& fsh) throw(Exception) : handles_(link(vsh, fsh))
            {
            }
            
            Program::Program(const std::string& vsh, const std::string& fsh) throw(Exception, Shader::Exception) :
            handles_(link(Shader(ShaderType::VERTEX, vsh), Shader(shader::ShaderType::FRAGMENT, fsh)))
            {
            }
            
            Program::ProgramHandles Program::link(const Shader& vsh, const Shader& fsh) throw (Exception) {
                GLuint handle = glCreateProgram();
                std::map<VariableDeclaration, GLuint> uniformMapping;
                
                try {
                    GLint compileOk;
                    GLint errLength;
                    GLchar* errMsg;
                    
                    glAttachShader(handle, vsh.handle());
                    glAttachShader(handle, fsh.handle());
                    
                    int inputLoc = 0;
                    for(VariableDeclaration v : vsh.inputs()) {
                        glBindAttribLocation(handle, inputLoc++, v.name().c_str());
                    }
                    
                    
                    glLinkProgram(handle);
                    glGetProgramiv(handle, GL_LINK_STATUS, &compileOk);
                    if(!compileOk) {
                        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &errLength);
                        errMsg = new GLchar[errLength];
                        glGetProgramInfoLog(handle, errLength, &errLength, errMsg);
                        throw Exception(errMsg);
                    }
                    
                    for(VariableDeclaration u : vsh.uniforms()) {
                        GLuint loc = glGetUniformLocation(handle, u.name().c_str());
                        uniformMapping[u] = loc;
                    }
                    
                    for(VariableDeclaration u : fsh.uniforms()) {
                        GLuint loc = glGetUniformLocation(handle, u.name().c_str());
                        uniformMapping[u] = loc;
                    }
                    
                } catch(...) {
                    glDeleteProgram(handle);
                    throw;
                }
                
                return Program::ProgramHandles{
                    handle,
                    uniformMapping
                };
            }
            
            const GLuint Program::uniformLocation(const VariableDeclaration& u) const
            {
                auto it = handles_.uniforms.find(u);
                if(it == handles_.uniforms.end()) {
                    std::cerr << u.name() << std::endl;
                    throw Exception("unknown uniform");
                } else {
                    return it->second;
                }
            }

            
            Program::Program(const Program&& p) throw() : handles_(p.handles_) {
                p.handles_.programId = 0;
            }
            
            Program::~Program() {
                if(handles_.programId) {
                    glDeleteProgram(handles_.programId);
                }
            }
            
            ProgramUse::ProgramUse(const Program& p) : program_(p) {
                glUseProgram(program_.handles().programId);
            }
            
            ProgramUse::~ProgramUse() {
                glUseProgram(0);
            }
            
            void ProgramUse::setUniformf(const std::string& name, GLfloat value) const
            {
                glUniform1f(program_.uniformLocation(VariableDeclaration(name, VariableDeclaration::Type::FLOAT)), value);
            }
            
            
            void ProgramUse::setUniformi(const std::string& name, GLuint value) const
            {
                glUniform1i(program_.uniformLocation(VariableDeclaration(name, VariableDeclaration::Type::SAMPLER2D)), value);
            }
            
            void ProgramUse::setUniform(const std::string& name, const math::Vec2<GLfloat>& value) const
            {
                glUniform2f(program_.uniformLocation(VariableDeclaration(name, VariableDeclaration::Type::VEC2)), value.x, value.y);
            }
            
            void ProgramUse::setUniform(const std::string& name, const math::Vec3<GLfloat>& value) const
            {
                glUniform3f(program_.uniformLocation(VariableDeclaration(name, VariableDeclaration::Type::VEC3)), value.x, value.y, value.z);
            }
            
            void ProgramUse::setUniform(const std::string& name, const math::Vec4<GLfloat>& value) const
            {
                glUniform4f(program_.uniformLocation(VariableDeclaration(name, VariableDeclaration::Type::VEC4)), value.x, value.y, value.z, value.w);
            }
            
            void ProgramUse::setUniform(const std::string& name, const math::Mat4<GLfloat>& value) const
            {
                glUniformMatrix4fv(program_.uniformLocation(VariableDeclaration(name, VariableDeclaration::Type::MAT4)), 1, GL_FALSE, &value[0][0]);
            }
        }
    }
}