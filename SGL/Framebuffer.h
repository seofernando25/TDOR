//
// Created by fer on 10/13/2021.
//

#ifndef TDOR_FRAMEBUFFER_H
#define TDOR_FRAMEBUFFER_H

#include "glad.h"
#include "Texture.h"

namespace SGL {
    class Framebuffer {
    public:
        Framebuffer();
        ~Framebuffer();
        GLuint GetID() { return ID; }
        void AttachTexture(Texture *texture, int colorIndex = 0);
        bool IsComplete();
        void Resize(int w, int h);
        void SetViewport();
        void Bind();
        static void Unbind(){ glBindFramebuffer(GL_FRAMEBUFFER, 0); }
    private:
        int width = 100;
        int height = 100;
        GLuint ID;
        GLuint depthStencil;
        Texture* texture;

        void Rebuild();

    };
}

#endif //TDOR_FRAMEBUFFER_H
