//
// Created by fer on 10/11/2021.
//

#ifndef TDOR_BUFFERLAYOUT_H
#define TDOR_BUFFERLAYOUT_H


#include <initializer_list>
#include "glad/glad.h"

struct BufferElement
{
    GLuint dataType;
    bool normalized;
    GLuint size;
    GLuint offset;
};

class BufferLayout{
public:
    BufferLayout() {};

    BufferLayout(std::initializer_list<int> elements);
    unsigned int GetStride();
private:
    std::vector<BufferElement> elements;
};


#endif //TDOR_BUFFERLAYOUT_H
