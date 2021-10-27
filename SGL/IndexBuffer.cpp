//
// Created by fer on 10/11/2021.
//


#include "IndexBuffer.h"

SGL::IndexBuffer::IndexBuffer() {
    glGenBuffers(1, &ID);
    iCount = 0;
}

SGL::IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &ID);
}

void SGL::IndexBuffer::SetIndices(std::vector<GLuint> *indices) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(GLuint), indices->data(), GL_STATIC_DRAW);
    iCount = indices->size();
}

void SGL::IndexBuffer::Bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}
