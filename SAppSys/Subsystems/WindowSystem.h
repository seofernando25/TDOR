//
// Created by fer on 10/11/2021.
//

#ifndef TDOR_WINDOWSUBSYSTEM_H
#define TDOR_WINDOWSUBSYSTEM_H

#include "SDL.h"
#include "glad/glad.h"
#include <queue>

class WindowSubsystem {
public:
    WindowSubsystem();
    ~WindowSubsystem();
    void PumpEvents();
    void* GetWindowRef();
    void* GetGLContext();
    void GetCursorPosition(int* px, int* py);
    void GetMouseDelta(int* dx, int* dy);
    void CreateWindow(const char* name, int width, int height, bool windowed);
    void DestroyWindow();
    void EventTimeout(int ms);
    void SwapWindow();
    void MoveWindow(int x, int y);
    void ResizeWindow(int w, int h);
private:
    SDL_Window * window;
    SDL_GLContext GLContext;

    std::queue<SDL_Event> eventBuffer;

    bool hasFocus;
    bool isFullScreen;
    int renderedWidth;
    int rendererHeight;

    int windowWidth;
    int windowHeight;

    int mouseXDelta;
    int mouseYDelta;

    int mouseDownX;
    int mouseDownY;

    bool mouseDown;
    bool doubleClick;
    int mouseDownTimeStamp;
};


#endif //TDOR_WINDOWSUBSYSTEM_H
