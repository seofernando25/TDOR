//
// Created by fer on 10/11/2021.
//

#ifndef TDOR_VERTEXARRAY_H
#define TDOR_VERTEXARRAY_H

#include "glad.h"
#include <vector>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace SGL {

    class VertexArray {
    public:
        VertexArray();

        ~VertexArray();

        GLuint SetIndices(std::vector<GLuint> *indices);
        void Draw();
        template <typename  T>
        GLuint AddVertexAttrib(std::vector<T> *array, BufferElement layout, int attribLocation){
            glBindVertexArray(ID);
            // Creates the VBO
            GLuint vbo;
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, array->size() * sizeof(float), array->data(), GL_STATIC_DRAW);

            // Binds the VBO to a location
            glEnableVertexAttribArray(attribLocation);
            glVertexAttribPointer(attribLocation,
                                  layout.itemCount,
                                  layout.dataType,
                                  layout.normalized ? GL_TRUE : GL_FALSE,
                                  layout.GetStride(),
                                  (void*)0);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            return vbo;
        }

        void Bind();

        GLuint GetID() { return ID; }

    private:
        GLuint ID;
        int indicesCnt = 0;
    };
}

#endif //TDOR_VERTEXARRAY_H
