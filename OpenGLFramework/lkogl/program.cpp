//
//  program.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 11.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "program.h"

namespace lkogl {
    namespace graphics {
        Program::Program(const Shader& vsh, const Shader& fsh) throw(lkogl::graphics::ShaderException) : handles_(link(vsh, fsh))
        {
        }
        
        Program::Program(const std::string& vsh, const std::string& fsh) throw(lkogl::graphics::ShaderException) :
        handles_(link(Shader(graphics::ShaderType::VERTEX, vsh), Shader(graphics::ShaderType::FRAGMENT, fsh)))
        {
        }
        
        Program::ProgramHandles Program::link(const Shader& vsh, const Shader& fsh) throw (ShaderException) {
            GLuint handle = glCreateProgram();
            GLint mMat, vpMat, samplerPos, ambientPos, eysPos, specIntPos, specPowPos, dirLightColPos, dirLightIntPos, dirLightDirPos,
            pntLightColPos, pntLightIntPos, pntLightPosPos, pntLightRangePos,
            pntLightAttCPos, pntLightAttLPos, pntLightAttQPos,
            
            sptLightColPos, sptLightIntPos, sptLightPosPos, sptLightRangePos,
            sptLightAttCPos, sptLightAttLPos, sptLightAttQPos,
            sptDirectionPos, sptLightCutoffPos,
            
            smpPosPosition,
            smpNormPosition,
            smpColPosition;
            
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
                vpMat = glGetUniformLocation(handle, "uViewProjMatrix");
                samplerPos = glGetUniformLocation(handle, "uSampler");
                ambientPos = glGetUniformLocation(handle, "uAmbientIntensity");
                
                eysPos = glGetUniformLocation(handle, "uEyePosition");
                specIntPos = glGetUniformLocation(handle, "uMaterial.specularIntensity");
                specPowPos = glGetUniformLocation(handle, "uMaterial.specularPower");
                dirLightColPos = glGetUniformLocation(handle, "uDirectionalLight.base.color");
                dirLightIntPos = glGetUniformLocation(handle, "uDirectionalLight.base.intensity");
                dirLightDirPos = glGetUniformLocation(handle, "uDirectionalLight.direction");
                
                
                
                pntLightColPos = glGetUniformLocation(handle, "uPointLight.base.color");
                pntLightIntPos = glGetUniformLocation(handle, "uPointLight.base.intensity");
                pntLightPosPos = glGetUniformLocation(handle, "uPointLight.position");
                pntLightRangePos = glGetUniformLocation(handle, "uPointLight.range");
                pntLightAttCPos = glGetUniformLocation(handle, "uPointLight.attenuation.constant");
                pntLightAttLPos = glGetUniformLocation(handle, "uPointLight.attenuation.linear");
                pntLightAttQPos = glGetUniformLocation(handle, "uPointLight.attenuation.quadratic");
                
                sptLightColPos = glGetUniformLocation(handle, "uSpotLight.pointLight.base.color");
                sptLightIntPos = glGetUniformLocation(handle, "uSpotLight.pointLight.base.intensity");
                sptLightPosPos = glGetUniformLocation(handle, "uSpotLight.pointLight.position");
                sptLightRangePos = glGetUniformLocation(handle, "uSpotLight.pointLight.range");
                sptLightAttCPos = glGetUniformLocation(handle, "uSpotLight.pointLight.attenuation.constant");
                sptLightAttLPos = glGetUniformLocation(handle, "uSpotLight.pointLight.attenuation.linear");
                sptLightAttQPos = glGetUniformLocation(handle, "uSpotLight.pointLight.attenuation.quadratic");
                sptDirectionPos = glGetUniformLocation(handle, "uSpotLight.direction");
                sptLightCutoffPos = glGetUniformLocation(handle, "uSpotLight.cutoff");
                
                smpPosPosition = glGetUniformLocation(handle, "uSamplerPosition");
                smpNormPosition = glGetUniformLocation(handle, "uSamplerNormal");
                smpColPosition = glGetUniformLocation(handle, "uSamplerColor");
                
            } catch(...) {
                glDeleteProgram(handle);
                throw;
            }
            
            return Program::ProgramHandles{
                handle, mMat, vpMat, samplerPos, ambientPos,
                eysPos, specIntPos, specPowPos, dirLightColPos, dirLightIntPos, dirLightDirPos,
                pntLightColPos, pntLightIntPos, pntLightPosPos, pntLightRangePos,
                pntLightAttCPos, pntLightAttLPos, pntLightAttQPos,
                
                sptLightColPos, sptLightIntPos, sptLightPosPos, sptLightRangePos,
                sptLightAttCPos, sptLightAttLPos, sptLightAttQPos,
                sptDirectionPos, sptLightCutoffPos,
                
                smpPosPosition,
                smpNormPosition,
                smpColPosition
            };
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
        
        ModelMatrixUse::ModelMatrixUse(const Program& prog,
                                       const math::Mat4<GLfloat>& modelMat) {
            glUniformMatrix4fv(prog.handles().modelMatrixPosition, 1, GL_FALSE, &modelMat[0][0]);
        }
        
        ModelMatrixUse::~ModelMatrixUse() {
        }
        
        CameraMatrixUse::CameraMatrixUse(const Program& prog,
                                         const math::Mat4<GLfloat>& viewProjectionMat,
                                         const math::Vec3<GLfloat>& cameraPosition) {
            glUniformMatrix4fv(prog.handles().viewProjectionMatrixPosition, 1, GL_FALSE, &viewProjectionMat[0][0]);
            glUniform3f(prog.handles().eyePosition, cameraPosition.x, cameraPosition.y, cameraPosition.z);
        }
        
        CameraMatrixUse::~CameraMatrixUse() {
        }
    }
}