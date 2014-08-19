//
//  mouse_tracker.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 16.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "pointer_tracking.h"

namespace lkogl {
    namespace ui {
        
        PointerTracking::PointerTracking(std::shared_ptr<Element> root) : root_(root)
        {}
        
        PointerTracking::~PointerTracking()
        {}
        
        void PointerTracking::track(const math::Vec2<int>& pos)
        {
            
            if(recentPos_ != pos) {
                auto newElementList = tester_.test(root_, pos);
                std::set<std::shared_ptr<Element>> newElementSet;
                newElementSet.insert(newElementList.begin(), newElementList.end());
                
                for(auto ri=contactedElementSet_.begin();ri!=contactedElementSet_.end();)
                {
                    if(newElementSet.find(*ri) == newElementSet.end()) {
                        (*ri)->onContactCancel();
                        contactedElementSet_.erase(ri++);
                    } else {
                        ri++;
                    }
                }
                
                for(auto ri=recentElementList_.rbegin();ri!=recentElementList_.rend();++ri)
                {
                    if(newElementSet.find(*ri) == newElementSet.end()) {
                        (*ri)->onBlur();
                    }
                }
                
                for(auto ri=newElementList.rbegin();ri!=newElementList.rend();++ri)
                {
                    if(recentElementSet_.find(*ri) == recentElementSet_.end()) {
                        (*ri)->onFocus();
                    }
                }
                
                if(capturedElement_.get()) {
                    capturedElement_->onContactMove(pos);
                }
                
                
                recentElementList_ = newElementList;
                recentElementSet_ = newElementSet;
                recentPos_ = pos;
            }
        }
        
        void PointerTracking::beginPointing(const math::Vec2<int>& pos)
        {
            for(auto ri=recentElementList_.rbegin();ri!=recentElementList_.rend();++ri)
            {
                if(!(*ri)->onContactBegin(pos)) {
                    capturedElement_ = *ri;
                    break;
                } else {
                    contactedElementSet_.insert(*ri);
                }
            }
        
        }
        
        void PointerTracking::endPointing(const math::Vec2<int>& pos)
        {
            
            for(auto ri=contactedElementSet_.rbegin();ri!=contactedElementSet_.rend();ri++)
            {
                (*ri)->onContactEnd(pos);
            }
            contactedElementSet_.clear();
            
            if(capturedElement_.get()) {
                capturedElement_->onContactEnd(pos);
            }
            capturedElement_.reset();
        }
    }
}