//
//  leaf.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "leaf.h"

namespace lkogl {
    namespace scene {
        Leaf::Leaf(graphics::Model model) : model_(std::move(model))
        {
        }
        
        Leaf::~Leaf() {
        
        }
        
        const graphics::Model& Leaf::model() const {
            return model_;
        }
        
        void Leaf::accept( const Visitor &v ) const {
            v.visit(*this);
        }
    }
}