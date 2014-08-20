//
//  window.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//
#include "./window.h"

namespace lkogl {
    namespace loop {
        Window::Window(int width, int height, std::string title) throw (Exception) {
            SDL_Init(SDL_INIT_VIDEO);
            int imgFlags = IMG_INIT_PNG;
            
            if((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
                SDL_Quit();
                IMG_Quit();
                throw Exception(std::string("Image Loader could not be initialized: ") + IMG_GetError());
            }
            
            int audioFlags = MIX_INIT_MP3;
            if((Mix_Init(audioFlags) & audioFlags) != audioFlags) {
                SDL_Quit();
                IMG_Quit();
                Mix_Quit();
                throw Exception(std::string("Audio module could not be initialized: ") + Mix_GetError());
            }
            
            if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
                SDL_Quit();
                IMG_Quit();
                Mix_Quit();
                throw Exception(std::string("Audio module could not be initialized: ") + Mix_GetError());
            }
            
            
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, 1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
            SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 1 );

            int windowOptions = SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE|SDL_WINDOW_SHOWN;
            
            displayWindow_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width, height, windowOptions);
            
            SDL_GLContext glContext_ = SDL_GL_CreateContext(displayWindow_);
            
            if (!glContext_)
            {
                SDL_DestroyWindow(displayWindow_);
                SDL_Quit();
                throw Exception("OpenGL context could not be created.");
            }
        }
        
        void Window::refreshDisplay() const {
            SDL_GL_SwapWindow(displayWindow_);
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
            SDL_GL_DeleteContext(glContext_);
            SDL_DestroyWindow(displayWindow_);
            IMG_Quit();
            Mix_CloseAudio();
            while(Mix_Init(0)) {
                Mix_Quit();
            }
            SDL_Quit();
        }
    }
}