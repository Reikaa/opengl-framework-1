//
//  game_loop.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 07.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__game_loop__
#define __OpenGLFramework__game_loop__

#include <vector>
#include <iostream>

#include "./window.h"

namespace lkogl {
    namespace loop {
        long fps(long fps);
        
        long hirestime();
        
        long lowrestime();
        
        class InputHandler {
        public:
            virtual bool processEvent(const SDL_Event&) const = 0;
        };
        
        class DefaultDelegate {
        public:
            
            const bool stopped = false;
            
            bool mouseLocked = true;
            
            void setUp() const {
            }
            
            void tearDown() const {
            }
            
            void processEvent(const SDL_Event& e) const {
            }
            
            void input() const {
            }
            
            void update() const {
            }
            
            void render() const {
            }
            
            void resize(int width, int height) const {
            }
            
            void report(int frameCount, int updateCount, long frameTimeAvg) const {
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
                delegate_.resize(900,600);
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
                const long updateDuration = fps(60);
            } state_;
        public:
            class Exception {
            public:
                Exception(const std::string& msg) {}
                ~Exception() {}
            };
            
            Loop(const DELEGATE& del) : delegate_(del), window_(900,600, "Loading...") {
                window_.setTitle(del.title());
            }
            
            ~Loop() {
            
            }
            
            void start() const  {
                if(state_.running) {
                    throw Exception("already running");
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
                long renderTimeSum = 0;
                int updates = 0;
                state_.running = true;
                int mouseLocked = false;
                int updated = false;
                bool lockChanged = true;

                
                while(state_.running && !delegate_.stopped)
                {
                    
                    state_.lastTime = currentTime;
                    currentTime = hirestime();
                    state_.nanoDelta = currentTime - state_.lastTime;
                    state_.behind += state_.nanoDelta;
                    
                    
                    while(state_.behind > state_.updateDuration) {
                        if(mouseLocked != delegate_.mouseLocked) {
                            mouseLocked = delegate_.mouseLocked;
                            SDL_SetRelativeMouseMode(mouseLocked ? SDL_TRUE : SDL_FALSE);
                            
                            lockChanged  = true;
                            SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
                            SDL_PumpEvents();
                            SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);

                        }
                        
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
                                case SDL_MOUSEMOTION:
                                    // skip the first motion event after the
                                    // mouse lock has been toggled to prevent
                                    // SDL from reporting a huge relative position
                                    // change
                                    if(lockChanged) {
                                        lockChanged = false;
                                        continue;
                                    }
                                    break;
                            }
                            
                            processEvent(e);
                        }
                        
                        input();
                        
                        update();
                        
                        updates++;
                        updated = true;
                    }
                    
                    if(lowrestime() - time >= 1) {
                        long avgRender = frames==0 ? renderTimeSum : renderTimeSum/frames;
                        delegate_.report(frames, updates, avgRender);
                        time = lowrestime();
                        frames = 0;
                        updates = 0;
                        renderTimeSum = 0;
                        window_.setTitle(delegate_.title());
                    }
                    
                    if(updated) {
                        long beforeRender = hirestime();
                        
                        render();
                        state_.renderTime = hirestime()-beforeRender;
                        window_.refreshDisplay();
                        
                        frames++;
                        renderTimeSum += state_.renderTime;
                        
                        updated = false;
                    }
                }
                
                state_.running = false;
                
            }

            void stop() const {
                state_.running = false;
            }
            
            
        private:
            void input() const {
                delegate_.input();
            }

            void processEvent(const SDL_Event& e) const {
                delegate_.processEvent(e);
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
