//
//  aabb3.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 21.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef OpenGLFramework_aabb3_h
#define OpenGLFramework_aabb3_h

#include "../vec3.h"

namespace lkogl {
    namespace math {
        namespace geo {
            
            template<typename T>
            struct Aabb3 {
                Vec3<T> min;
                Vec3<T> max;
                
                Aabb3(const Vec3<T>& minp, const Vec3<T>& maxp) :min(minp), max(maxp) {}
                ~Aabb3() {}
                
                std::array<Vec3<T>, 8> corners() const
                {
                    std::array<Vec3<T>, 8> corners;
                    
                    corners[0] = min;
                    corners[1] = min + Vec3<T>{max.x,0,0};
                    corners[2] = min + Vec3<T>{max.x,max.y,0};
                    corners[3] = min + Vec3<T>{0,max.y,0};
                    corners[4] = min + Vec3<T>{0,max.y,max.z};
                    corners[5] = min + Vec3<T>{0,0,max.z};
                    corners[6] = min + Vec3<T>{max.x,0,max.z};
                    corners[7] = max;
                    
                    return corners;
                }
            };
        }
    }
}

#endif
