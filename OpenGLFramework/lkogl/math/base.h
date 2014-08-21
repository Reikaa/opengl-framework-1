//
//  base.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 21.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__base__
#define __OpenGLFramework__base__

#include <limits>
#include <math.h>


namespace lkogl {
    namespace math {        
        template<typename T>
        T radians(const T& deg) {
            static_assert(std::numeric_limits<T>::is_iec559, "'radians' only accept floating-point input");
            return deg * 2 * M_PI / 360.f;
        }
        
        float radians(const int& deg);
        
        
        template<typename T>
        T max(const T& a, const T& b) {
            return a>b?a:b;
        }
        
        template<typename T>
        T min(const T& a, const T& b) {
            return a<b?a:b;
        }
    }
}


#endif /* defined(__OpenGLFramework__base__) */
