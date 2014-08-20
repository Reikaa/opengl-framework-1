//
//  render_target.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 13.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__render_target__
#define __OpenGLFramework__render_target__

#include <vector>

#include "./texture.h"

namespace lkogl {
    namespace graphics {
        struct Screen {
            int width, height;
        };
        
        class MainTargetUse {
        public:
            MainTargetUse();
            ~MainTargetUse();
        };
        
        struct TargetType {
            GLenum attachment;
            GLenum format;
        };
        
        class FrameBufferResource {
            const GLenum textureTarget_ = GL_TEXTURE_2D;
            const int width_;
            const int height_;
            
            const struct Handle {
                GLuint frameBuffer;
                GLuint renderBuffer;
                std::vector<TextureResource> textures_;
            } handles_;
            
        public:
            class Exception {
            public:
                Exception(const std::string& m) {}
                ~Exception() {}
            };
            FrameBufferResource(int width, int height, std::vector<TargetType> targets) throw(Exception);
            ~FrameBufferResource();
            
            const TextureResource& getTextureResource(int num) const;
        private:
            Handle generate(std::vector<TargetType> targets) const throw (Exception);
            
            friend class FrameBufferBinding;
        };
        
        
        class FrameBufferBinding {
            const FrameBufferResource& r_;
        public:
            FrameBufferBinding(const FrameBufferResource& r);
            
            ~FrameBufferBinding();
        };

        
        class FrameBuffer {
            const std::shared_ptr<FrameBufferResource> resource_;
        public:
            explicit FrameBuffer(int width, int height, std::vector<TargetType>);
            FrameBuffer(const FrameBuffer&);
            ~FrameBuffer();
                        
            friend class BufferTargetUse;
            friend class BufferTextureUse;
        };
        
        class BufferTargetUse {
            FrameBufferBinding b_;
        public:
            BufferTargetUse(const FrameBuffer&);
            ~BufferTargetUse();
        };
        
        class BufferTextureUse {
            TextureBinding b_;
        public:
            BufferTextureUse(const shader::ProgramUse& loc, const std::string& uniform, const FrameBuffer&, GLuint num, GLuint slot);
            ~BufferTextureUse();
        };
    }
}

#endif /* defined(__OpenGLFramework__render_target__) */
