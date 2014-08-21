//
//  triangle3.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 21.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef OpenGLFramework_triangle3_h
#define OpenGLFramework_triangle3_h

namespace lkogl {
    namespace math {
        namespace geo {
            
            template<typename T>
            struct Triangle3 {
                Vec3<T> a;
                Vec3<T> b;
                Vec3<T> c;
                
                Triangle3(const Vec3<T>& p1, const Vec3<T>& p2, const Vec3<T>& p3) : a(p1), b(p2), c(p3)
                {}
                
                ~Triangle3() {}
                
                std::array<Vec3<T>, 3> corners() const
                {
                    return { a, b, c };
                }
                
                Vec3<T> normal()
                {
                    return cross(a-b,c-b);
                }
            };
        }
    }
}

#endif
