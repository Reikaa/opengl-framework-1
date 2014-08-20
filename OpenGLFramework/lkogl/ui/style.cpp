//
//  style.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 16.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./style.h"

namespace lkogl {
    namespace ui {
        const Color& Style::background() const
        {
            return backgroundColor_;
        }
        
        void Style::setBackground(const Color& col)
        {
            backgroundColor_ = col;
        }
        
        bool Style::overflow() const
        {
            return overflow_;
        }
        
        void Style::setOverflow(bool col)
        {
            overflow_ = col;
        }
    }
}