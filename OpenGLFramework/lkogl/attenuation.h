//
//  attenuation.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 10.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__attenuation__
#define __OpenGLFramework__attenuation__

namespace lkogl {
    namespace graphics {
        namespace lighting {
            class Attenuation {
            public:
                float constant_;
                float linear_;
                float quadratic_;
                Attenuation(float c, float l, float q);
                
                float calc(float x) const;
                float solve(float y) const;
            };
        }
    }
}

#endif /* defined(__OpenGLFramework__attenuation__) */
