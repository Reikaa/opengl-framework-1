//
//  length.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 16.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__length__
#define __OpenGLFramework__length__

namespace lkogl {
    namespace ui {
        class Length {
            float abs_;
            float rel_;
        public:
            
            int calc(int par) const {
                return abs_+rel_*par;
            }
            Length(int length) : abs_(length), rel_(0)
            {}
            Length() : abs_(1), rel_(0)
            {}
        private:
            Length(float abs, float rel) : abs_(abs), rel_(rel)
            {}
            friend const Length px(int p);
            friend const Length percent(int p);
            friend const Length fill(int p);
            
        public:            
            // operators
            
            Length operator+= (const Length& b);
            
            Length operator-= (const Length& b);
        };
        
        const Length px(int p);
        const Length percent(int p);
        const Length fill(int p);
        
        Length operator+ (const Length& a, const Length& b);
        
        Length operator- (const Length& a, const Length& b);
        
    }
}

#endif /* defined(__OpenGLFramework__length__) */
