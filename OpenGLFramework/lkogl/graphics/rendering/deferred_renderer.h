//
//  deferred_renderer.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 14.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__deferred_renderer__
#define __OpenGLFramework__deferred_renderer__

#include "../shader/program.h"
#include "../../scene/scene.h"
#include "../render_target.h"
#include "../material.h"
#include "../geometry_object.h"
#include "../../camera/camera.h"

namespace lkogl {
    namespace graphics {
        namespace rendering {
            class DeferredRenderer {
                struct Programs {
                    shader::Program skybox_;
                    shader::Program deferredGeo_;
                    shader::Program deferredAmbient_;
                    shader::Program deferredStencil_;
                    shader::Program deferredDir_;
                    shader::Program deferredPoint_;
                    shader::Program deferredSpot_;
                    shader::Program quadtree_;
                } programs_;
                std::unique_ptr<FrameBuffer> buffer_;
                struct {
                    int x, y, width, height;
                } viewport_;
                Screen screen_;
                int ratioWidth_, ratioHeight_;
                GeometryObject square_;
                GeometryObject box_;
                Texture sky_;
                mutable int entityCount_ = 0;
            public:
                mutable bool drawBoxes_ = false;
                
                DeferredRenderer(const Screen& screen, int ratioW, int ratioH) throw (graphics::shader::Shader::Exception);;
                ~DeferredRenderer();
                
                void render(const scene::Scene& graph, const camera::Camera& cam) const;
                
                void resize(int w, int h);
                
                int entityCount() const { return entityCount_; }
                
            private:
                Programs initPrograms() throw (graphics::shader::Shader::Exception);
            };
        }
    }
}

#endif /* defined(__OpenGLFramework__deferred_renderer__) */
