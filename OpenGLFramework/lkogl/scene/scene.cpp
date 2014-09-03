//
//  scene.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 24.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./scene.h"

namespace lkogl {
    namespace scene {
        Scene::Scene() : tree_(math::elements::Aabb3<float>(128,128,128))
        {}
        Scene::~Scene()
        {}
        
        const lkogl::math::graphs::Octree<float, Entity>& Scene::tree() const
        {
            return tree_;
        }
        
        void Scene::addEntity(std::shared_ptr<Entity> e)
        {
            tree_.insert(e);
        }
        
        void Scene::removeEntity(std::shared_ptr<Entity> e)
        {
            tree_.remove(e);
        }
    }
}