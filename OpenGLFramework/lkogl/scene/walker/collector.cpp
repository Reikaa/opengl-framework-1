//
//  collector.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 21.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include <queue>
#include "collector.h"

namespace lkogl {
    namespace scene {
        namespace walker {
            Collector::Collector() {}
            Collector::~Collector() {}
                
            std::vector<std::shared_ptr<const Node>> Collector::collect(const std::shared_ptr<Node> start, const Predicate& p) const
            {
                std::vector<std::shared_ptr<const Node>> result;
                
                std::queue<std::shared_ptr<const Node>> queue;
                queue.push(start);
                
                while(!queue.empty()) {
                    std::shared_ptr<const Node> current = queue.front();
                    queue.pop();
                    
                    if(p(*current.get())) {
                        result.push_back(current);
                    }
                    
                    auto children = current->children_;
                    for(auto const c : children) {
                        queue.push(c);
                    }
                }
                
                return result;
            }
            
        }
        
    }
}