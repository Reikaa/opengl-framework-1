//
//  entity_transformation.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 25.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__entity_transformation__
#define __OpenGLFramework__entity_transformation__

#include "../geometry/transformation.h"

namespace lkogl {
    namespace scene {
        class EntityTransformation {
            geometry::Transformation transformation_;
            math::Mat4<float> parentTransform_;
            
            mutable bool dirty_=true;
            mutable bool dirtyInverse_=true;
            mutable math::Mat4<float> cacheMatrix_;
            mutable math::Mat4<float> cacheInverse_;
        public:
            EntityTransformation();
            ~EntityTransformation();
            
            void setTranslation(const math::Vec3<float>& t);
            void setScale(const math::Vec3<float>& s);
            void setRotation(const math::Quat<float>& r);
            
            void transform(const geometry::Transformation& t);
            
            math::Vec3<float> translation() const;
            math::Vec3<float> scale() const;
            math::Quat<float> rotation() const;
            
            void setParent(const math::Mat4<float>& parent, bool keepPos = true);

            const math::Mat4<float>& matrix() const;
            const math::Mat4<float>& inverseMatrix() const;
        };
    }
}

#endif /* defined(__OpenGLFramework__entity_transformation__) */
