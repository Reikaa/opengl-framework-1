//
//  shader_loader.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 26.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__shader_loader__
#define __OpenGLFramework__shader_loader__

#include "../../graphics/shader/shader.h"
#include "../../utils/file_path.h"

namespace lkogl {
    namespace resources {
        namespace shader_loader {
            class ShaderLoader {
                const utils::Path path_;
            public:
                class Exception {
                public:
                    std::string msg;
                    Exception(const std::string& m) : msg(m) {}
                    ~Exception() {}
                };
                
                ShaderLoader();
                ShaderLoader(const utils::Path& path);
                ~ShaderLoader();
                
                graphics::shader::Shader fromFile(graphics::shader::ShaderType, const std::string&) const throw (Exception, graphics::shader::Shader::Exception);
            };
        }
    }
}

#endif /* defined(__OpenGLFramework__shader_loader__) */
