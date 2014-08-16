//
//  program.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 11.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__program__
#define __OpenGLFramework__program__

#include "shader.h"

namespace lkogl {
    namespace graphics {
        class Program {
            struct ProgramHandles {
                mutable GLuint programId;
                
                GLint farPosition;
                GLint modelMatrixPosition;
                GLint viewProjectionMatrixPosition;
                
                GLint samplerPosition;
                GLint ambientIntensityPosition;
                GLint colorPosition;
                GLint eyePosition;
                
                GLint specularIntensityPosition;
                GLint specularPowerPosition;
                
                GLint directionalLightColorPosition;
                GLint directionalLightIntensityPosition;
                GLint directionalLightDirectionPosition;
                
                GLint pointLightColorPosition;
                GLint pointLightIntensityPosition;
                GLint pointLightPositionPosition;
                GLint pointLightRangePosition;
                GLint pointLightAttenuationCPosition;
                GLint pointLightAttenuationLPosition;
                GLint pointLightAttenuationQPosition;
                
                GLint spotLightColorPosition;
                GLint spotLightIntensityPosition;
                GLint spotLightPositionPosition;
                GLint spotLightRangePosition;
                GLint spotLightAttenuationCPosition;
                GLint spotLightAttenuationLPosition;
                GLint spotLightAttenuationQPosition;
                GLint spotLightDirectionPosition;
                GLint spotLightCutoffPosition;
                
                GLint samplerPosPosition;
                GLint samplerNormPosition;
                GLint samplerColPosition;
            } handles_;
            
        public:
            Program(const std::string& vsh, const std::string& fsh) throw (ShaderException);
            Program(const Shader& vsh, const Shader& fsh) throw (ShaderException);
            Program(const Program&&) throw();
            ~Program();
            
            const ProgramHandles& handles() const { return handles_; }
        private:
            ProgramHandles link(const Shader& vsh, const Shader& fsh) throw (ShaderException);
            
        };
        
        class ProgramUse {
            const Program& program_;
        public:
            ProgramUse(const Program&);
            ~ProgramUse();
        };
        
        class ModelMatrixUse {
        public:
            ModelMatrixUse(const Program&,
                           const math::Mat4<GLfloat>& modelMat);
            ~ModelMatrixUse();
        };
        
        class CameraMatrixUse {
        public:
            CameraMatrixUse(const Program&,
                            const math::Mat4<GLfloat>& viewProjectionMat,
                            const math::Vec3<GLfloat>& cameraPosition,
                            float far);
            ~CameraMatrixUse();
        };
    }
}

#endif /* defined(__OpenGLFramework__program__) */
