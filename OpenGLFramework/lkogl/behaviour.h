//
//  behaviour.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 16.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__behaviour__
#define __OpenGLFramework__behaviour__

namespace lkogl {
    namespace ui {
        
        class Element;
        
        class Behaviour
        {
        public:
            virtual ~Behaviour();
            
            virtual void onInit(Element& el) = 0;
            virtual bool onFocus(Element& el) = 0;
            virtual bool onBlur(Element& el) = 0;
            virtual bool onContactBegin(Element& el) = 0;
            virtual bool onContactEnd(Element& el) = 0;
            virtual bool onContactMove(Element& el) = 0;
            virtual bool onContactCancel(Element& el) = 0;
        };
        
    }
}

#endif /* defined(__OpenGLFramework__behaviour__) */
