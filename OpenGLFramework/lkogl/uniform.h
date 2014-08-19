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

#include "opengl.h"


namespace lkogl {
    namespace graphics {
        class Uniform {
        public:
            enum class Type {
                FLOAT,
                VEC2,
                VEC3,
                VEC4,
                MAT4,
                SAMPLER2D
            };
        private:
            std::string name_;
            Type type_;
        public:
            Uniform(const std::string& name, Type type);
            ~Uniform();
            
            const std::string& name() const;
            const Type type() const;
        };
        
        inline bool operator<(const Uniform& lhs, const Uniform& rhs)
        {
            return lhs.name() < rhs.name();
        }
    }
}

#endif /* defined(__OpenGLFramework__uniform__) */
