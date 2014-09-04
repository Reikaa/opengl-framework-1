//
//  image_high_map.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 17.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__image_height_map__
#define __OpenGLFramework__image_height_map__

#include "../../utils/image.h"

#include "./index_model.h"

namespace lkogl {
    namespace resources {
        namespace mesh_loader {
            class ImageHeightMap {
                float* const points_;
                const int width_;
                const int height_;
            public:
                ImageHeightMap(int width, int height);
                ~ImageHeightMap();
                
                void setHeightAt(int x, int y, float h);
                
                IndexModel toIndexedModel() const;

                std::vector<std::pair<math::Vec3<float>, IndexModel>> toIndexedModel(int parts) const;
            };
            
            ImageHeightMap heigh_map_from_image(const utils::Image& img, unsigned short filterRadius = 3);
        }
    }
}


#endif /* defined(__OpenGLFramework__high_map__) */
