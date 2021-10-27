//
// Created by fer on 10/11/2021.
//

#ifndef TDOR_INDEXBUFFER_H
#define TDOR_INDEXBUFFER_H


#include "glad.h"
#include <vector>

namespace SGL {

    class IndexBuffer {
    public:
        IndexBuffer();

        ~IndexBuffer();

        void SetIndices(std::vector<GLuint> *indices);

        GLuint GetIndiceCount() { return iCount; }

        GLuint GetID() { return ID; }

        void Bind();

    private:
        GLuint iCount;
        GLuint ID;

    };
}

#endif //TDOR_INDEXBUFFER_H
