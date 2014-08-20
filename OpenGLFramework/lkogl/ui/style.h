//
//  style.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 16.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__style__
#define __OpenGLFramework__style__

#include "../math/math.h"

namespace lkogl {
    namespace ui {
        typedef math::Vec4<float> Color;
        
        class Style
        {
            Color backgroundColor_ = {0,0,0,0.3};
            
        public:
            Style() {};
            const Color& background() const;
            
            void setBackground(const Color& col);
            
        };
    }
}

#endif /* defined(__OpenGLFramework__style__) */
