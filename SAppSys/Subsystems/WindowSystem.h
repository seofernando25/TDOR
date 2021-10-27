//
// Created by fer on 10/11/2021.
//

#ifndef TDOR_WINDOWSYSTEM_H
#define TDOR_WINDOWSYSTEM_H


#include "SubSystem.h"
#include "spch.h"

class WindowSystem: public SubSystem {
public:
    WindowSystem();
    ~WindowSystem();
    void PumpEvents();
    SDL_Window * GetWindowRef();
    void GetCursorPosition(int* px, int* py);
    void GetMouseDelta(int* dx, int* dy);
    void CreateWindow(const char* name, int width, int height, bool windowed);
    void DestroyWindow();
    void EventTimeout(int ms);
    void SwapWindow();
    void MoveWindow(int x, int y);
    void ResizeWindow(int w, int h);

    void Init() override;

    void Run() override;

    void Shutdown() override;

private:
    SDL_Window * window;

    std::queue<SDL_Event> eventBuffer;

    bool shouldClose;
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


#endif //TDOR_WINDOWSYSTEM_H
