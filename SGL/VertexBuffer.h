//
// Created by fer on 10/11/2021.
//

#ifndef TDOR_VERTEXBUFFER_H
#define TDOR_VERTEXBUFFER_H


#include "glad.h"
#include "BufferElement.h"
#include <vector>

namespace SGL {
    class VertexBuffer {
    public:
        VertexBuffer();

        ~VertexBuffer();

        template<typename T> void SubData(std::vector<T> *vertices, GLintptr offset){
            glBindBuffer(GL_ARRAY_BUFFER, ID);
            glBufferSubData(GL_ARRAY_BUFFER, offset, vertices->size() * sizeof(T), vertices->data());
        }

        template<typename T> void SetData(std::vector<T> *vertices){
                glBindBuffer(GL_ARRAY_BUFFER, ID);
                glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(T), vertices->data(), GL_DYNAMIC_DRAW);
        }

        GLuint GetID() { return ID; }
        void Bind();

        BufferElement bufferLayout;
    private:
        GLuint ID;


    };
}

#endif //TDOR_VERTEXBUFFER_H
