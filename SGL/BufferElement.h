//
// Created by fer on 10/11/2021.
//

#ifndef TDOR_BUFFERELEMENT_H
#define TDOR_BUFFERELEMENT_H

#include <cstddef>
#include "glad.h"

namespace SGL {
    class BufferElement {
    public:
        BufferElement(GLuint dataT = GL_FLOAT, GLuint itemCnt = 3, bool normalized = false): dataType(dataT), itemCount(itemCnt), normalized(normalized){}

        GLuint dataType;
        GLuint itemCount;
        bool normalized;

        size_t GetDataTypeSize() {
            switch (dataType) {
                case GL_INT:
                    return sizeof(int);
                case GL_UNSIGNED_INT:
                    return sizeof(unsigned int);
                case GL_BOOL:
                    return sizeof(bool);
                case GL_FLOAT:
                    return sizeof(float);
            }
            return 0;
        }

        size_t GetStride()  {
            return GetDataTypeSize() * itemCount;
        }
    };
}
#endif //TDOR_BUFFERELEMENT_H
