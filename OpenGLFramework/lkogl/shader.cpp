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
        
        Shader::Shader(const Shader&& s) throw() : handle_(s.handle_) {
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
        
    }
}