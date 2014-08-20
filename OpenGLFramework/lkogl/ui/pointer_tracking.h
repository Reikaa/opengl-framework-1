//
//  mouse_tracker.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 16.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__mouse_tracker__
#define __OpenGLFramework__mouse_tracker__

#include <set>

#include "element.h"
#include "hittester.h"

namespace lkogl {
    namespace ui {
        
        class PointerTracking
        {
            const std::shared_ptr<Element> root_;
            const HitTester tester_;

            math::Vec2<int> recentPos_;
            std::set<std::shared_ptr<Element>> recentElementSet_;
            std::vector<std::shared_ptr<Element>> recentElementList_;
            
            mutable std::set<std::shared_ptr<Element>> contactedElementSet_;
            std::shared_ptr<Element> capturedElement_;
        public:
            PointerTracking(std::shared_ptr<Element> root);
            
            ~PointerTracking();
            
            void track(const math::Vec2<int>& pos);
            void beginPointing(const math::Vec2<int>& pos);
            void endPointing(const math::Vec2<int>& pos);
        };
        
    }
}

#endif /* defined(__OpenGLFramework__mouse_tracker__) */
