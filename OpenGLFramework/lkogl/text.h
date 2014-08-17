//
//  text.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 08.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__text__
#define __OpenGLFramework__text__

#include <string>

namespace lkogl {
    namespace utils {
        class FileException {};
        
        class PlainText {
        public:
            const std::string content;
            PlainText(const std::string name) throw (FileException);
            ~PlainText();
        private:
            const std::string read(const std::string name) const;
        };
    }
}

#endif /* defined(__OpenGLFramework__text__) */
