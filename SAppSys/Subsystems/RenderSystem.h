//
// Created by fer on 10/12/2021.
//

#ifndef TDOR_RENDERSYSTEM_H
#define TDOR_RENDERSYSTEM_H

#include "spch.h"
#include "SubSystem.h"
#include "WindowSystem.h"

class RenderSystem: public SubSystem {
public:
    WindowSystem* windowSystem;

    void Init() override {
        SDL_LogVerbose(SDL_LOG_CATEGORY_SYSTEM,  "Initializing Render Subsystem");
    }

    void Run() override {
        // Wait until we actually have the window
        while(windowSystem->GetWindowRef() == nullptr);

        // Initialize OpenGL context
        auto GLContext = SDL_GL_CreateContext(windowSystem->GetWindowRef());
        if (GLContext == nullptr){
            SDL_LogCritical(SDL_LOG_CATEGORY_RENDER, "Failed to create GL context: %s", SDL_GetError());
        }

        SDL_GL_MakeCurrent(windowSystem->GetWindowRef(), GLContext); // Free's the window to be able to pass

        gladLoadGLLoader(SDL_GL_GetProcAddress);

        int major = 0;
        int minor = 0;
        SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
        SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
        SDL_LogVerbose(SDL_LOG_CATEGORY_RENDER,  "OpenGL Properties:");
        SDL_LogVerbose(SDL_LOG_CATEGORY_RENDER,  "Vendor: %s", glGetString(GL_VENDOR));
        SDL_LogVerbose(SDL_LOG_CATEGORY_RENDER,  "Renderer: %s", glGetString(GL_RENDERER));
        SDL_LogVerbose(SDL_LOG_CATEGORY_RENDER,  "Version: %s", glGetString(GL_VERSION));


        Shader s;
        s.AddShader(
                "#version 330 core\n"
                "out vec4 FragColor;\n"
                "\n"
                "void main()\n"
                "{\n"
                "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                "}",
                GL_FRAGMENT_SHADER);

        s.AddShader(
                "#version 330 core\n"
                "layout (location = 0) in vec3 aPos;\n"
                "void main()\n"
                "{\n"
                "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                "}",
                GL_VERTEX_SHADER);

        s.Validate();



        std::vector<float> vertices = {
                0.5f,  0.5f, 0.0f,  // top right
                0.5f, -0.5f, 0.0f,  // bottom right
                -0.5f, -0.5f, 0.0f,  // bottom left
                -0.5f,  0.5f, 0.0f   // top left
        };
        std::vector<GLuint> indices = {  // note that we start from 0!
                0, 1, 3,   // first triangle
                1, 2, 3    // second triangle
        };

        SGL::VertexArray vao;
        vao.AddVertexAttrib(&vertices, SGL::BufferElement(GL_FLOAT, 3, false), 0);
        vao.SetIndices(&indices);

        s.Bind();
        while(!shouldClose){
            /*
             * Implementation works with, a given context and a list of cameras
             * For each camera setup their properties (view projection matrix) and
             * check if they should clear the render target and how.
             *
             *
             */

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            vao.Draw();

            // Drawing passes go here

            windowSystem->SwapWindow();
        }

        SDL_GL_DeleteContext(GLContext);
    }

    void Shutdown() override {
        shouldClose = true;
    }
private:
    bool shouldClose = false;
};

#endif //TDOR_RENDERSYSTEM_H
