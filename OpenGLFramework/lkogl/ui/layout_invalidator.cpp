//
//  layout_invalidator.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 16.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include <queue>

#include "layout_invalidator.h"

namespace lkogl {
    namespace ui {
        
        LayoutInvalidator::LayoutInvalidator()
        {}
        
        LayoutInvalidator::~LayoutInvalidator()
        {}
            
        void LayoutInvalidator::invalidate(std::shared_ptr<Element> el) const
        {
            std::queue<std::shared_ptr<Element>> elements;
            
            elements.push(el);
            
            while(!elements.empty()) {
                std::shared_ptr<Element> current = elements.front();
                elements.pop();
                bool selfDirty = current->layout().dirty();
                
                for(const auto c : current->children()) {
                    elements.push(c);
                    if(selfDirty) {
                        c->layout().invalidate();
                    }
                }
                
            }

        }

        
    }
}