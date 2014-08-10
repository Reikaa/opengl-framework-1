//
//  game_loop.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__game_loop__
#define __OpenGLFramework__game_loop__

#include "window.h"

constexpr long operator "" _fps(unsigned long long int fps) {
    return 1000000000 / fps;
}

namespace lkogl {
    namespace loop {
        long hirestime();
        
        long lowrestime();
        
        class DefaultDelegate {
        public:
            void setUp() const {
            }
            
            void tearDown() const {
            }
            
            void input() const {
            }
            
            void update() const {
            }
            
            void render() const {
            }
            
            void resize(int width, int height) const {
            }
            
            const std::string title() const {
                return "Untitled";
            }
            
            ~DefaultDelegate() {
                
            }
        };

        
        template <typename DELEGATE = DefaultDelegate>
        class Looping {
            const DELEGATE& delegate_;
        public:
            Looping(const DELEGATE& del) : delegate_(del) {
                delegate_.setUp();
            }
            
            ~Looping() {
                delegate_.tearDown();
            }
        };
        
        template <typename DELEGATE>
        class Loop {
            const Window window_;
            const DELEGATE& delegate_;
            mutable struct LoopState {
                long behind = 0;
                long lastTime = 0;
                long nanoDelta = 0;
                long renderTime = 0;
                bool running = false;
                const long updateDuration = 60_fps;
            } state_;
        public:
            Loop(const DELEGATE& del) : delegate_(del), window_(900,600, "Loading...") {
                window_.setTitle(del.title());
            }
            
            ~Loop() {
            
            }
            
            void start() const  {
                if(state_.running) {
                    throw "already running";
                }
                
                Looping<DELEGATE> l(delegate_);
                resize(window_.width(), window_.height());
                
                state_.behind = state_.updateDuration + 1;
                state_.lastTime = hirestime();
                long currentTime = state_.lastTime;
                state_.nanoDelta = 0;
                
                SDL_Event e;
                long time = lowrestime();
                int frames = 0;
                int updates = 0;
                state_.running = true;
                
                while(state_.running)
                {
                    
                    state_.lastTime = currentTime;
                    currentTime = hirestime();
                    state_.nanoDelta = currentTime - state_.lastTime;
                    state_.behind += state_.nanoDelta;
                    
                    
                    while(state_.behind > state_.updateDuration) {
                        state_.behind -= state_.updateDuration;
                        while( SDL_PollEvent( &e ) != 0 )
                        {
                            switch(e.type) {
                                case SDL_QUIT:
                                    stop();
                                    break;
                                case SDL_WINDOWEVENT:
                                    switch (e.window.event)
                                    {
                                        case SDL_WINDOWEVENT_RESIZED:
                                            int windowWidth = e.window.data1;
                                            int windowHeight = e.window.data2;
                                            resize(windowWidth, windowHeight);
                                    }
                                    break;
                            }
                        }
                        
                        input();
                        
                        update();
                        
                        updates++;
                    }
                    
                    if(lowrestime() - time >= 1) {
                        time = lowrestime();
                        frames = 0;
                        updates = 0;
                    }
                    
                    long beforeRender = hirestime();
                    
                    render();
                    
                    state_.renderTime = hirestime()-beforeRender;
                    window_.refreshDisplay();
                }
                
            }

            void stop() const {
                state_.running = false;
            }
            
            
        private:
            void input() const {
                delegate_.input();
            }

            void update() const {
                delegate_.update();
            }
            
            void render() const {
                delegate_.render();
            }
            
            void resize(int w, int h) const {
                delegate_.resize(w, h);
            }
        };
        
    }
}

#endif /* defined(__OpenGLFramework__game_loop__) */
