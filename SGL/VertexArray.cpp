//
// Created by fer on 10/11/2021.
//

#include <SDL2/SDL_log.h>
#include "VertexArray.h"

SGL::VertexArray::VertexArray() {
    glGenVertexArrays(1, &ID);
}

SGL::VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &ID);
}

void SGL::VertexArray::Bind() {
    glBindVertexArray(ID);
}


GLuint SGL::VertexArray::SetIndices(std::vector<GLuint> *indices) {
    Bind();
    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(GLuint), indices->data(), GL_STATIC_DRAW);
    indicesCnt = indices->size();
    return ibo;
}

void SGL::VertexArray::Draw() {
    Bind();
    glDrawElements(GL_TRIANGLES, indicesCnt, GL_UNSIGNED_INT, 0);
}
