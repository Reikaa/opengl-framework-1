//
//  window.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//
#include "window.h"

namespace lkogl {
    namespace loop {
        Window::Window(int width, int height, std::string title) {
            SDL_RendererInfo displayRendererInfo;
            
            SDL_Init(SDL_INIT_VIDEO);
            
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
            
            int windowOptions = SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE|SDL_WINDOW_SHOWN;
            
            SDL_CreateWindowAndRenderer(width, height, windowOptions, &displayWindow_, &displayRenderer_);
            SDL_SetWindowTitle(displayWindow_, title.c_str());
            
            SDL_GetRendererInfo(displayRenderer_, &displayRendererInfo);
            
            if ((displayRendererInfo.flags & SDL_RENDERER_ACCELERATED) == 0)
            {
                SDL_DestroyWindow(displayWindow_);
                SDL_Quit();
                throw 0;
            }
        }
        
        void Window::refreshDisplay() const {
            SDL_RenderPresent(displayRenderer_);
        }
        
        int Window::width() const
        {
            int w;
            int h;
            SDL_GetWindowSize(displayWindow_, &w, &h);
            
            return w;
        }
        
        int Window::height() const
        {
            int w;
            int h;
            SDL_GetWindowSize(displayWindow_, &w, &h);
            
            return h;
        }
        
        void Window::setTitle(const std::string& title) const
        {
            SDL_SetWindowTitle(displayWindow_, title.c_str());
        }
        
        Window::~Window() {
            SDL_DestroyRenderer(displayRenderer_);
            SDL_DestroyWindow(displayWindow_);
            SDL_Quit();
        }
    }
}