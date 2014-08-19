//
//  uniform.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 19.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "uniform.h"

namespace lkogl {
    namespace graphics {
        
        Uniform::Uniform(const std::string& name, Type type) :
        name_(name), type_(type)
        {
        }
        
        Uniform::~Uniform()
        {
        }
        
        const std::string& Uniform::name() const
        {
            return name_;
        }
        
        const Uniform::Type Uniform::type() const
        {
            return type_;
        }
    }
}