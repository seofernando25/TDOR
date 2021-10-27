//
// Created by fer on 10/11/2021.
//

#include "Texture.h"

SGL::Texture::Texture(int w, int h, void *pixels) {
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    width = w;
    height = h;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

SGL::Texture::~Texture() {
    glDeleteTextures(1, &ID);
}

void SGL::Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, ID);
}

int SGL::Texture::GetWidth() const {
    return width;
}

int SGL::Texture::GetHeight() const {
    return height;
}
