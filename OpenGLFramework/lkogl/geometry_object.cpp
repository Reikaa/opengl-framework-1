//
//  geometry_object.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 11.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "geometry_object.h"
#include "shader.h"

namespace lkogl {
    namespace graphics {
    
        GeometryObjectResource::GeometryObjectResource() {
            glGenVertexArrays(1, &vertexArrayObject_);
            glBindVertexArray(vertexArrayObject_);
            glGenBuffers(2, &buffers_.vertexBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, buffers_.vertexBuffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers_.indexBuffer);
            glBindVertexArray(0);
        }
        
        GeometryObjectResource::~GeometryObjectResource() {
            glDeleteVertexArrays(1, &vertexArrayObject_);
            glDeleteBuffers(2, &buffers_.vertexBuffer);
        }
        
        GeometryObject::GeometryObject(const geometry::Mesh& mesh) : resource_(std::make_shared<GeometryObjectResource>()), indexCount_((GLuint)mesh.triangles.size()*3)
        {
            buffer(mesh);
        }
        
        GeometryObject::GeometryObject(const GeometryObject& go) : resource_(go.resource_), indexCount_(go.indexCount_) {
        }
        
        GeometryObject::~GeometryObject() {
        }
        
        void GeometryObject::buffer(const geometry::Mesh& mesh) {
            GeometryObjectResource::Binding b(*resource_.get());
            
            glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(geometry::Vertex), &mesh.vertices[0], GL_STATIC_DRAW);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.triangles.size() * sizeof(geometry::Triangle), &mesh.triangles[0], GL_STATIC_DRAW);
            
            // Enable vertex attributes
            glEnableVertexAttribArray(PointerLocation::LOCATION_POSITION);
            glVertexAttribPointer(PointerLocation::LOCATION_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(geometry::Vertex), (const GLvoid *) offsetof(geometry::Vertex, position));
            
            glEnableVertexAttribArray(PointerLocation::LOCATION_NORMAL);
            glVertexAttribPointer(PointerLocation::LOCATION_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(geometry::Vertex), (const GLvoid *) offsetof(geometry::Vertex, normal));
            
            glEnableVertexAttribArray(LOCATION_COLOR);
            glVertexAttribPointer(PointerLocation::LOCATION_COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(geometry::Vertex), (const GLvoid *) offsetof(geometry::Vertex, color));
            
            glEnableVertexAttribArray(PointerLocation::LOCATION_TEXTURE_COORDS);
            glVertexAttribPointer(PointerLocation::LOCATION_TEXTURE_COORDS, 4, GL_FLOAT, GL_FALSE, sizeof(geometry::Vertex), (const GLvoid *) offsetof(geometry::Vertex, textureCoord));
        }
        
        GeometryObjectUse::GeometryObjectUse(const GeometryObject& geo) : binding_(*geo.resource_.get()), geometry_(geo) {
        }
        GeometryObjectUse::~GeometryObjectUse() {
        }
        
        void GeometryObjectUse::render() const {
            glDrawElements(GL_TRIANGLES, geometry_.indexCount(), GL_UNSIGNED_INT, (void*)0);
        }
    }
}