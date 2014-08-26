//
//  uniform.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 19.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__uniform__
#define __OpenGLFramework__uniform__

#include <string>

#include "../../opengl.h"


namespace lkogl {
    namespace graphics {
        namespace shader {
            class VariableDeclaration {
            public:
                enum class Type {
                    FLOAT,
                    VEC2,
                    VEC3,
                    VEC4,
                    MAT4,
                    MAT3,
                    SAMPLER2D
                };
            private:
                std::string name_;
                Type type_;
            public:
                VariableDeclaration(const std::string& name, Type type);
                ~VariableDeclaration();
                
                const std::string& name() const;
                const Type type() const;
            };
            
            inline bool operator<(const VariableDeclaration& lhs, const VariableDeclaration& rhs)
            {
                return lhs.name() < rhs.name();
            }
        }
    }
}

#endif /* defined(__OpenGLFramework__uniform__) */
