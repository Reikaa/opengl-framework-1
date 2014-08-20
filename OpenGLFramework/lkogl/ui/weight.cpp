//
//  weight.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 16.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./weight.h"

namespace lkogl {
    namespace ui {
        
        WeightLinear WeightLinear::Center{1,1};
        WeightLinear WeightLinear::Left{1,0};
        WeightLinear WeightLinear::Right{0,1};
        
        WeightLinear WeightLinear::Top{1,0};
        WeightLinear WeightLinear::Bottom{0,1};

    }
}