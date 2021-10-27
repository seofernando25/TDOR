//
// Created by fer on 10/11/2021.
//

#include "VertexBuffer.h"

SGL::VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &ID);
}


void SGL::VertexBuffer::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

SGL::VertexBuffer::VertexBuffer() {
    glGenBuffers(1, &ID);
}
