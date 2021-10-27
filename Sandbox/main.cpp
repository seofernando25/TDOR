//
// Created by fer on 10/11/2021.
//

#include "spch.h"
#include "Subsystems/RenderSystem.h"
#include "App.h"


int main(int argc, char *argv[])
{
    App app;
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
    WindowSystem window;
    RenderSystem render;
    render.windowSystem = &window;
    int i = 5;

    app.AddSubsystem("window", &window);
    app.AddSubsystem("render", &render);
    app.JoinSubsystems();
    return 0;
}