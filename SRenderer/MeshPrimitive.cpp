//
// Created by fer on 10/13/2021.
//

#include "MeshPrimitive.h"



void MeshPrimitive::UploadMesh() {
    // Clean VBOs
    glDeleteBuffers(vbos.size(), vbos.data());
    vbos.clear();

    vao.SetIndices(&indices);
    GLuint vbo;
    vbo = vao.AddVertexAttrib(&position, SGL::BufferElement(GL_FLOAT, 3), MeshLocations::POSITION);
    vbos.push_back(vbo);
    vbo = vao.AddVertexAttrib(&normal, SGL::BufferElement(GL_FLOAT, 3), MeshLocations::NORMAL);
    vbos.push_back(vbo);
    vbo = vao.AddVertexAttrib(&tangent, SGL::BufferElement(GL_FLOAT, 4), MeshLocations::TANGENT);
    vbos.push_back(vbo);
    vbo = vao.AddVertexAttrib(&color, SGL::BufferElement(GL_FLOAT, 4), MeshLocations::COLOR);
    vbos.push_back(vbo);
    vbo = vao.AddVertexAttrib(&texCoord, SGL::BufferElement(GL_FLOAT, 2), MeshLocations::TEXCOORD);
    vbos.push_back(vbo);
}

void MeshPrimitive::Draw() {
    vao.Draw();
}

