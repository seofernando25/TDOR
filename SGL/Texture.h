//
// Created by fer on 10/11/2021.
//

#ifndef TDOR_TEXTURE_H
#define TDOR_TEXTURE_H

#include "glad.h"

namespace SGL {

    class Texture {
    public:
        Texture(int w, int h, void *pixels = nullptr);

        ~Texture();

        void Bind();

        GLuint GetID() { return ID; }

        int GetWidth() const;

        int GetHeight() const;

    private:
        GLuint ID;
        int width = 0;
        int height = 0;
    };
}

#endif //TDOR_TEXTURE_H
