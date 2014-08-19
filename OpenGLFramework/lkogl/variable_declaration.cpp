//
//  uniform.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 19.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "variable_declaration.h"

namespace lkogl {
    namespace graphics {
        
        VariableDeclaration::VariableDeclaration(const std::string& name, Type type) :
        name_(name), type_(type)
        {
        }
        
        VariableDeclaration::~VariableDeclaration()
        {
        }
        
        const std::string& VariableDeclaration::name() const
        {
            return name_;
        }
        
        const VariableDeclaration::Type VariableDeclaration::type() const
        {
            return type_;
        }
    }
}