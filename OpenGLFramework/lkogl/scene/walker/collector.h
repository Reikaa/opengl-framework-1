//
//  collector.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 21.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__collector__
#define __OpenGLFramework__collector__

#include <functional>
#include <vector>

#include "../node.h"

namespace lkogl {
    namespace scene {
        namespace walker {
            class Collector
            {
            public:
                typedef std::function< bool(const Node&) > Predicate;
                
                Collector();
                ~Collector();
                
                std::vector<std::shared_ptr<const Node>> collect(const std::shared_ptr<Node>, const Predicate&) const;
            };
            
        }
        
    }
}

#endif /* defined(__OpenGLFramework__collector__) */
