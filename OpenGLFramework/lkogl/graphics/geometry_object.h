//
//  geometry_object.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 11.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__geometry_object__
#define __OpenGLFramework__geometry_object__

#include "../geometry/mesh.h"

namespace lkogl {
    namespace graphics {
        class GeometryObjectResource {
            GLuint vertexArrayObject_;
            struct {
                GLuint vertexBuffer;
                GLuint indexBuffer;
            } buffers_;
        public:
            
            class Binding {
            public:
                Binding(const GeometryObjectResource& res) {
                    glBindVertexArray(res.vertexArrayObject_);
                };
                
                ~Binding() {
                    glBindVertexArray(0);
                };
            };
            
            GeometryObjectResource();
            GeometryObjectResource(const GeometryObjectResource&) = delete;
            GeometryObjectResource(GeometryObjectResource&&) = delete;
            ~GeometryObjectResource();
        };
        
        class GeometryObject {
            enum PointerLocation {
                POSITION,
                NORMAL,
                TEXTURE_COORDS
            };
            
            std::shared_ptr<GeometryObjectResource> resource_;
            int indexCount_;
        public:
            GeometryObject() = delete;
            explicit GeometryObject(const geometry::Mesh&);
            GeometryObject(const GeometryObject&);
            ~GeometryObject();
            
            //const GeometryHandle& handle() const { return handles_; }
            int indexCount() const { return indexCount_; }
        private:
            void buffer(const geometry::Mesh& mesh);
            friend class GeometryObjectUse;
        };
        
        class GeometryObjectUse {
            const GeometryObjectResource::Binding binding_;
            const GeometryObject& geometry_;
        public:
            GeometryObjectUse(const GeometryObject&);
            ~GeometryObjectUse();
            
            void render() const;
        };
    }
}

#endif /* defined(__OpenGLFramework__geometry_object__) */
