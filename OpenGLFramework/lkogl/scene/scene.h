//
//  scene.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 24.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__scene__
#define __OpenGLFramework__scene__

#include <vector>

#include "../math/graphs/octree.h"
#include "./entity.h"

namespace lkogl {
    namespace scene {
        typedef std::function< bool(const Entity&) > Predicate;
        
        class Scene {
            std::vector<std::shared_ptr<Entity>> entities_;
            lkogl::math::graphs::Octree<float, Entity, &Entity::boundingBox> tree_;
        public:
            Scene();
            ~Scene();
            
            void addEntity(std::shared_ptr<Entity>);
            void removeEntity(std::shared_ptr<Entity>);
            
            void update();
            
            const lkogl::math::graphs::Octree<float, Entity>& tree() const;
            
            const std::vector<std::shared_ptr<Entity>>& all();
        };
    }
}

#endif /* defined(__OpenGLFramework__scene__) */
