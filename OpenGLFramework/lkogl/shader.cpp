//
//  shader.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "shader.h"

namespace lkogl {
    namespace graphics {
        ShaderException::ShaderException(const std::string& s): msg(s) {}
        ShaderException::~ShaderException() {}
        
        Shader::Shader(ShaderType type, const std::string& source) throw(lkogl::graphics::ShaderException) : handle_(compile(type, source)) {
            
        }
        
        Shader::Shader(Shader&& s) throw() : handle_(s.handle_) {
            s.handle_ = 0;
        }
        
        Shader::~Shader() {
            if(handle_) {
                glDeleteShader(handle_);
            }
        }
        
        GLuint Shader::compile(ShaderType type, const std::string& source) throw (ShaderException) {
            GLuint shaderHandle = glCreateShader(static_cast<int>(type));

            try {
                GLint compileOk;
                GLint errLength;
                GLchar* errMsg;
                const GLchar* csource = source.c_str();
                const GLint lengths[] = {(GLint)source.length()};
                
                glShaderSource(shaderHandle, 1, &csource, lengths);
                glCompileShader(shaderHandle);
                
                glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileOk);
                if(!compileOk) {
                    glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &errLength);
                    errMsg = new GLchar[errLength];
                    glGetShaderInfoLog(shaderHandle, errLength, &errLength, errMsg);
                    
                    throw ShaderException(errMsg);
                }
                
                return shaderHandle;
            } catch(...) {
                glDeleteShader(shaderHandle);
                throw;
            }
        }
        
        Program::Program(const Shader& vsh, const Shader& fsh) throw(lkogl::graphics::ShaderException) : handles_(link(vsh, fsh))
        {
        }
        
        Program::Program(const std::string& vsh, const std::string& fsh) throw(lkogl::graphics::ShaderException) :
            handles_(link(Shader(graphics::ShaderType::VERTEX, vsh), Shader(graphics::ShaderType::FRAGMENT, fsh)))
        {
        }
        
        Program::ProgramHandles Program::link(const Shader& vsh, const Shader& fsh) throw (ShaderException) {
            GLuint handle = glCreateProgram();
            GLint mMat, vMat, pMat, camPos;
            
            try {
                GLint compileOk;
                GLint errLength;
                GLchar* errMsg;
                
                glAttachShader(handle, vsh.handle());
                glAttachShader(handle, fsh.handle());
                
                glBindAttribLocation(handle, LOCATION_POSITION, "vPosition");
                glBindAttribLocation(handle, LOCATION_NORMAL, "vNormal");
                glBindAttribLocation(handle, LOCATION_COLOR, "vColor");
                glBindAttribLocation(handle, LOCATION_TEXTURE_COORDS, "vTexCoord");

                glLinkProgram(handle);
                glGetProgramiv(handle, GL_LINK_STATUS, &compileOk);
                if(!compileOk) {
                    glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &errLength);
                    errMsg = new GLchar[errLength];
                    glGetProgramInfoLog(handle, errLength, &errLength, errMsg);
                    throw ShaderException(errMsg);
                }
                
                mMat = glGetUniformLocation(handle, "uModelMatrix");
                vMat = glGetUniformLocation(handle, "uViewMatrix");
                pMat = glGetUniformLocation(handle, "uProjectionMatrix");
                camPos = glGetUniformLocation(handle, "uCameraPosition");
            } catch(...) {
                glDeleteProgram(handle);
                throw;
            }
            
            return Program::ProgramHandles{handle, mMat, vMat, pMat, camPos};
        }

        Program::Program(Program&& p) throw() : handles_(p.handles_) {
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
        
        MatrixUse::MatrixUse(const Program& prog,
                             const math::Mat4<GLfloat>& modelMat,
                             const math::Mat4<GLfloat>& viewMat,
                             const math::Mat4<GLfloat>& projectionMat,
                             const math::Vec3<GLfloat>& cameraPosition) {
            glUniformMatrix4fv(prog.handles().modelMatrix, 1, GL_FALSE, &modelMat[0][0]);
            glUniformMatrix4fv(prog.handles().viewMatrix, 1, GL_FALSE, &viewMat[0][0]);
            glUniformMatrix4fv(prog.handles().projectionMatrix, 1, GL_FALSE, &projectionMat[0][0]);
            glUniform3f(prog.handles().cameraPosition, cameraPosition.x, cameraPosition.y, cameraPosition.z);
        }
        
        MatrixUse::~MatrixUse() {
            glUseProgram(0);
        }
        
        GeometryObject::GeometryObject(const geometry::Mesh& mesh) : handles_(buffer(mesh)), indexCount_((GLuint)mesh.triangles.size()*3)
        {
        }
        
        GeometryObject::GeometryObject(GeometryObject&& go) : handles_(go.handles_), indexCount_(go.indexCount_) {
            go.handles_ = { 0,0,0 };
            go.indexCount_ = 0;
        }
        
        GeometryObject::~GeometryObject() {
            if(handles_.object) {
                glDeleteVertexArrays(1, &handles_.object);
            }
            if(handles_.vertexBuffer) {
                glDeleteBuffers(2, &handles_.vertexBuffer);
            }
        }
        
        GeometryObject::GeometryHandle GeometryObject::buffer(const geometry::Mesh& mesh) {
            GeometryHandle handle;
            
            glGenVertexArrays(1, &handle.object);
            glBindVertexArray(handle.object);
            
            glGenBuffers(2, &(handle.vertexBuffer));
            
            glBindBuffer(GL_ARRAY_BUFFER, handle.vertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(geometry::Vertex), &mesh.vertices[0], GL_STATIC_DRAW);
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle.indexBuffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.triangles.size() * sizeof(geometry::Triangle), &mesh.triangles[0], GL_STATIC_DRAW);
            
            // Enable vertex attributes
            glEnableVertexAttribArray(PointerLocation::LOCATION_POSITION);
            glVertexAttribPointer(PointerLocation::LOCATION_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(geometry::Vertex), (const GLvoid *) offsetof(geometry::Vertex, position));
            
            glEnableVertexAttribArray(PointerLocation::LOCATION_NORMAL);
            glVertexAttribPointer(PointerLocation::LOCATION_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(geometry::Vertex), (const GLvoid *) offsetof(geometry::Vertex, normal));
            
            glEnableVertexAttribArray(LOCATION_COLOR);
            glVertexAttribPointer(PointerLocation::LOCATION_COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(geometry::Vertex), (const GLvoid *) offsetof(geometry::Vertex, color));
            
            glEnableVertexAttribArray(PointerLocation::LOCATION_TEXTURE_COORDS);
            glVertexAttribPointer(PointerLocation::LOCATION_TEXTURE_COORDS, 4, GL_FLOAT, GL_FALSE, sizeof(geometry::Vertex), (const GLvoid *) offsetof(geometry::Vertex, textureCoord));
            
            
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            return handle;
        }
        
        GeometryObjectUse::GeometryObjectUse(const GeometryObject& geo) : geometry_(geo) {
            glBindVertexArray(geometry_.handle().object);
        }
        GeometryObjectUse::~GeometryObjectUse() {
            glBindVertexArray(0);
        }
            
        void GeometryObjectUse::render() {
            glDrawElements(GL_TRIANGLES, geometry_.indexCount(), GL_UNSIGNED_INT, (void*)0);
        }
    }
}