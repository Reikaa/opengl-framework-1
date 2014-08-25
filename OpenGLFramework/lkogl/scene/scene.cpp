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
        Scene::Scene()
        {}
        Scene::~Scene()
        {}
            
        void Scene::addEntity(std::shared_ptr<Entity> e)
        {
            entities_.push_back(e);
        }
        
        void Scene::removeEntity(std::shared_ptr<Entity> e)
        {
            auto p = std::find(entities_.begin(), entities_.end(), e);
            entities_.erase(p);
        }
            
        std::vector<std::shared_ptr<Entity>> Scene::query(const Predicate& p)
        {
            std::vector<std::shared_ptr<Entity>> result;
            result.reserve(entities_.size()/3);
            
            for(auto e : entities_) {
                if(p(*e.get())) {
                    result.push_back(e);
                }
            }
            
            return result;
        }
        
        std::vector<std::shared_ptr<const Entity>> Scene::query(const Predicate& p) const
        {
            std::vector<std::shared_ptr<const Entity>> result;
            result.reserve(entities_.size()/3);
            
            for(auto e : entities_) {
                if(p(*e.get())) {
                    result.push_back(e);
                }
            }
            
            return result;
        }
    }
}