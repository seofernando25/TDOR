//
// Created by fer on 10/13/2021.
//

#ifndef TDOR_MESHPRIMITIVE_H
#define TDOR_MESHPRIMITIVE_H


#include "SGL.h"

enum MeshLocations{
    POSITION = 0,
    NORMAL = 1,
    TANGENT = 2,
    COLOR = 3,
    TEXCOORD = 4
};

class MeshPrimitive {
public:
    void UploadMesh();
    void Draw();

    std::vector<glm::vec3> position;
    std::vector<glm::vec3> normal;
    std::vector<glm::vec4> tangent;
    std::vector<glm::vec4> color;
    std::vector<glm::vec2> texCoord;
    std::vector<unsigned int> indices;
private:
    SGL::VertexArray vao;
    std::vector<GLuint> vbos;
};


#endif //TDOR_MESHPRIMITIVE_H
