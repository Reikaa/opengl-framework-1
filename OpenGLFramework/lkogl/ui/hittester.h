//
//  hittester.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 16.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__hittester__
#define __OpenGLFramework__hittester__

#include "./element.h"
#include <vector>

namespace lkogl {
    namespace ui {
        
        class HitTester
        {
        public:
            HitTester();
            ~HitTester();
            
            std::vector<std::shared_ptr<Element>> test(std::shared_ptr<Element> el, math::Vec2<int> hit) const;
        };
        
    }
}

#endif /* defined(__OpenGLFramework__hittest__) */
