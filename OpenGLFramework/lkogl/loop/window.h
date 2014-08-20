//
//  window.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__window__
#define __OpenGLFramework__window__

#include <string>

#include "sdl.h"
#include "opengl.h"

namespace lkogl {
    namespace loop {
        class Window {
            SDL_Window* displayWindow_;
            SDL_GLContext glContext_;
        public:
            class Exception {
            public:
                Exception(const std::string&) {}
                ~Exception() {}
            };
            Window(int width, int height, std::string title) throw (Exception);
            ~Window();
            
            int width() const;
            int height() const;
            
            void setTitle(const std::string&) const;
            
            void refreshDisplay() const;
        };
    }
}


#endif /* defined(__OpenGLFramework__window__) */
