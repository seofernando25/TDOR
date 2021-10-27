//
// Created by fer on 10/11/2021.
//

#include "AppWindow.h"

#include <iostream>
#include <string>


AppWindow::AppWindow() {
    if (!SDL_WasInit(SDL_INIT_VIDEO))
        if (SDL_Init(SDL_INIT_VIDEO) == -1){
            std::string error = "SDL_Init(SDL_INIT_VIDEO) failed: ";
            error.append(SDL_GetError());
            throw std::runtime_error(error);
        }

    window = nullptr;
    GLContext = nullptr;

    hasFocus = true;
    isFullScreen = false;
    renderedWidth = 0;
    rendererHeight = 0;

    windowWidth = 0;
    windowHeight = 0;

    mouseXDelta = 0;
    mouseYDelta = 0;

    mouseDownX = 0;
    mouseDownY = 0;

    mouseDown = false;
    doubleClick = false;
    mouseDownTimeStamp = 0;

    CreateWindow("win", 640, 480, true);
}

void AppWindow::PumpEvents() {
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        eventBuffer.push(e); // Push all events to a queue

        switch (e.type) {
            case SDL_MOUSEMOTION:
            {
                if (!hasFocus)
                    break;
                mouseXDelta += e.motion.xrel;
                mouseYDelta += e.motion.yrel;
                break;
            }

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            {
                int button = e.button.button;
                bool pressed = (e.type == SDL_MOUSEBUTTONDOWN) || (e.button.state == SDL_PRESSED);
                bool doublePress = false;
                if (pressed)
                {
                    const int double_click_time = 400;
                    const int double_click_size = 2;
                    if (mouseDown &&
                        ((int)(e.button.timestamp - mouseDownTimeStamp ) <= double_click_time ) &&
                        ( abs( e.button.x - mouseDownX ) <= double_click_size ) &&
                         ( abs( e.button.y - mouseDownY ) <= double_click_size ) )
                    {
                        doublePress = true;
                        mouseDown = false;

                        // Double click events
                        SDL_Event event;
                        SDL_memset(&event, 0, sizeof(event)); /* or SDL_zero(event) */
                        event.type = 1;
                        SDL_PushEvent(&event);
                    }
                    else
                    {
                        mouseDownTimeStamp = e.button.timestamp;
                        mouseDownX = e.button.x;
                        mouseDownY = e.button.y;
                        mouseDown = true;
                    }
                }
                break;
            }

            case SDL_MOUSEWHEEL:
            {
                int scroll = e.wheel.y;
                break;
            }

            case SDL_WINDOWEVENT:
            {
                switch (e.window.event) {
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                        hasFocus = true;
                        break;
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                        hasFocus = false;
                        break;
                }
                break;
            }
        }
    }
}

void *AppWindow::GetWindowRef() {
    return window;
}

void AppWindow::GetCursorPosition(int *px, int *py) {
    SDL_GetMouseState(px, py);
}

void AppWindow::GetMouseDelta(int *dx, int *dy) {
    *dx = mouseXDelta;
    *dy = mouseYDelta;

    mouseXDelta = mouseYDelta = 0.f;
}

AppWindow::~AppWindow() {
    DestroyWindow();
    SDL_GL_UnloadLibrary();
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void AppWindow::CreateWindow(const char *name, int width, int height, bool windowed) {
    isFullScreen = !windowed;
    int flags = SDL_WINDOW_OPENGL;
    if (!windowed)
        flags |= SDL_WINDOW_FULLSCREEN;
    window = SDL_CreateWindow(name,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width, height, flags);

    if (window == nullptr){
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to create SDL Window");
        std::string error = "Failed to create SDL window: ";
        error.append(SDL_GetError());
        throw std::runtime_error(error);
    }

    // Setup Full Screen
    if (isFullScreen){
        SDL_DisplayMode mode;
        SDL_GetWindowDisplayMode(window, &mode);
        SDL_SetWindowDisplayMode(window, &mode);
        SDL_SetWindowFullscreen(window, SDL_TRUE);
    }

    // Initialize OpenGL context
    GLContext = SDL_GL_CreateContext(window);
    if (GLContext == nullptr){
        SDL_LogCritical(SDL_LOG_CATEGORY_RENDER, "Failed to create GL context");
        std::string error = "Failed to create GL context: ";
        error.append(SDL_GetError());
        throw std::runtime_error(error);
    }

    SDL_GL_MakeCurrent(window, GLContext); // Set OpenGL context to the window



    windowHeight = height;
    windowWidth = width;
}

void AppWindow::EventTimeout(int ms) {
    SDL_WaitEventTimeout(nullptr, ms);
}

void AppWindow::SwapWindow() {
    SDL_GL_SwapWindow(window);
}

void AppWindow::MoveWindow(int x, int y) {
    SDL_SetWindowPosition(window, x, y);
}

void AppWindow::ResizeWindow(int w, int h) {
    windowWidth = w;
    windowHeight = h;

    SDL_SetWindowSize(window, w, h);

    // Reset window transformations
    glViewport(0, 0, w, h);
    glScissor(0, 0, w, h);
}

void AppWindow::DestroyWindow() {
    if(GLContext){
        SDL_GL_MakeCurrent(window, NULL);
        SDL_GL_DeleteContext(GLContext);
        GLContext = NULL;
    }

    if(window)
        SDL_DestroyWindow(window);
    window = nullptr;
}

void *AppWindow::GetGLContext() {
    return GLContext;
}

