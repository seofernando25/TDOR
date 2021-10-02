//
// Created by fer on 9/30/2021.
//

#ifndef TDOR_APPLICATION_H
#define TDOR_APPLICATION_H


#include <string>
#include <raylib.h>
#include <vector>
#include <Scene/Scene.h>

#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480


class Application {
public:
    Application(const std::string &name = "Stech", int window_w = DEFAULT_WIDTH, int window_h = DEFAULT_HEIGHT);

    void Run();

    RenderTexture2D renderTarget;
    static Application *instance;
    std::vector<Scene *> scenes;
};


#endif //TDOR_APPLICATION_H
