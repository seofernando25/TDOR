//
// Created by fer on 10/13/2021.
//

#include "Framebuffer.h"
#include "Texture.h"

bool SGL::Framebuffer::IsComplete() {
    Bind();
    return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

void SGL::Framebuffer::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, ID);
    glEnable(GL_DEPTH_TEST);
}

void SGL::Framebuffer::SetViewport(){
    glViewport(0, 0, width, height);
}

SGL::Framebuffer::Framebuffer() {
    Rebuild();
    texture = 0;
}

SGL::Framebuffer::~Framebuffer() {
    // Extra cleanup?
    Bind();
    glDeleteFramebuffers(1, &ID);
}

void SGL::Framebuffer::Rebuild(){
    // Clean everything and rebuild
    if(ID){
        glDeleteFramebuffers(1, &ID);
        glDeleteTextures(1, &depthStencil);
    }

    glGenFramebuffers(1, &ID);
    glBindFramebuffer(GL_FRAMEBUFFER, ID);

    // Create and bind depth stencil
    glGenTextures(1, &depthStencil);
    glBindTexture(GL_TEXTURE_2D, depthStencil);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_DEPTH24_STENCIL8,
                 width,
                 height,
                 0,
                 GL_DEPTH_STENCIL,
                 GL_UNSIGNED_INT_24_8,
                 nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthStencil, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SGL::Framebuffer::AttachTexture(Texture* texture, int colorIndex) {
    // Attach to buffer
    Bind();
    this->texture = texture;
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + colorIndex, GL_TEXTURE_2D, texture->GetID(), 0);
}

void SGL::Framebuffer::Resize(int w, int h) {
    width = w;
    height = h;

    Rebuild();
}
