//
//  render_target.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 13.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "render_target.h"

namespace lkogl {
    namespace graphics {
        
        
        MainTargetUse::MainTargetUse()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
        
        MainTargetUse::~MainTargetUse()
        {
        }
        
        FrameBufferResource::FrameBufferResource(int width, int height, std::vector<TargetType> targets) :
        handles_(generate(targets)), width_(width), height_(height)
        {
        }
        
        FrameBufferResource::~FrameBufferResource()
        {
            glDeleteFramebuffers(1, &handles_.frameBuffer);
            
            glDeleteRenderbuffers(1, &handles_.renderBuffer);
        }
        
        const TextureResource& FrameBufferResource::getTextureResource(int num) const
        {
            return handles_.textures_[num];
        }
        
        FrameBufferResource::Handle FrameBufferResource::generate(std::vector<TargetType> targets) const
        {
            Handle h;
            GLuint texturesRaw[targets.size()];
            
            constexpr GLuint MAX_BOUND = 32; //32 is the max number of bound textures in OpenGL
            GLuint numTargets = (GLuint)targets.size();
            bool hasDepth = false;
            
            if(targets.empty()) {
                throw "attachment type must be given";
            }
            
            if(numTargets > MAX_BOUND) {
                throw "too many attachments";
            }
            GLenum drawBuffers[targets.size()];
            
            glGenFramebuffers(1, &h.frameBuffer);
            glBindFramebuffer(GL_FRAMEBUFFER, h.frameBuffer);
            glGenTextures(numTargets, texturesRaw);
            
            
            for(int i=0;i<numTargets;i++) {
                h.textures_.push_back(std::move(TextureResource(texturesRaw[i], width_, height_)));
            }
            
            for(int i = 0; i < numTargets; i++)
            {
                if(targets[i].attachment == GL_DEPTH_ATTACHMENT)
                {
                    drawBuffers[i] = GL_NONE;
                    hasDepth = true;
                }
                else
                    drawBuffers[i] = targets[i].attachment;
                
                if(targets[i].attachment == GL_NONE)
                    continue;
                
                glBindTexture(GL_TEXTURE_2D, texturesRaw[i]);
                
                glTexParameteri(textureTarget_, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(textureTarget_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexParameteri(textureTarget_, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
                glTexParameteri(textureTarget_, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
                
                
                if(targets[i].attachment == GL_DEPTH_ATTACHMENT) {
                    glTexImage2D(textureTarget_, 0, GL_DEPTH_COMPONENT24, width_, height_, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
                } else {
                    glTexImage2D(textureTarget_, 0, targets[i].format, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
                }
                
                glFramebufferTexture2D(GL_FRAMEBUFFER, targets[i].attachment, textureTarget_, texturesRaw[i], 0);
            }
            
            if(!hasDepth)
            {
                glGenRenderbuffers(1, &h.renderBuffer);
                glBindRenderbuffer(GL_RENDERBUFFER, h.renderBuffer);
                glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width_, height_);
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, h.renderBuffer);
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, h.renderBuffer);

            }
            
            glDrawBuffers(numTargets, drawBuffers);
            
            GLenum err = glCheckFramebufferStatus(GL_FRAMEBUFFER);
            if(err != GL_FRAMEBUFFER_COMPLETE)
            {
                printf("framebuffer error: %d", err);
                exit(1);
            }
            
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            
            return h;
        }
        
        FrameBufferBinding::FrameBufferBinding(const FrameBufferResource& r) : r_(r) {
            glBindTexture(GL_TEXTURE_2D,0);
            glBindFramebuffer(GL_FRAMEBUFFER, r.handles_.frameBuffer);
        }
        
        FrameBufferBinding::~FrameBufferBinding() {
            glBindTexture(GL_TEXTURE_2D,0);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
        
        FrameBuffer::FrameBuffer(int width, int height, std::vector<TargetType> types) : resource_(std::make_shared<FrameBufferResource>(width, height, types))
        {
        }
        
        FrameBuffer::~FrameBuffer()
        {
        }
        
        BufferTargetUse::BufferTargetUse(const FrameBuffer& tex) :
        b_(*tex.resource_.get())
        {
            
        }
        
        BufferTargetUse::~BufferTargetUse()
        {
        }
        
        BufferTextureUse::BufferTextureUse(GLuint loc, const FrameBuffer& r, GLuint num, GLuint slot) :
        b_(r.resource_->getTextureResource(num), slot)
        {
            glUniform1i(loc, slot);
        }
        
        BufferTextureUse::~BufferTextureUse()
        {
        }
    }
}