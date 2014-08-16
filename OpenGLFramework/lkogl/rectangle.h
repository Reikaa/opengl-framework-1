//
//  rectangle.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 15.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__rectangle__
#define __OpenGLFramework__rectangle__

#include <stdio.h>
#include "math.h"

namespace lkogl {
    namespace ui {
        class Rectangle
        {
        public:
            typedef int ScalarType;
            typedef math::Vec2<ScalarType> Position;
            
        private:
            Position min_;
            Position max_;
            
        public:
            Rectangle();
            ~Rectangle();
            
            const Position center() const;
            void setCenter(const Position&);
            
            const Position topLeft() const;
            const Position topRight() const;
            const Position bottomLeft() const;
            const Position bottomRight() const;

            const Position size() const;

            const ScalarType left() const;
            const ScalarType right() const;
            const ScalarType top() const;
            const ScalarType bottom() const;
            
            const ScalarType width() const;
            const ScalarType height() const;
            
            void setSize(const ScalarType& width, const ScalarType& height);
            void setTopLeft(const Position& p);
        };
    }
}

#endif /* defined(__OpenGLFramework__rectangle__) */
