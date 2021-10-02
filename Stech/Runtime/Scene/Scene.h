//
// Created by fer on 9/30/2021.
//

#ifndef SCENE_H
#define SCENE_H


#include <string>
#include <vector>
#include <raylib.h>
#include <Entities/Entity.h>
#include <Entities/ECamera.h>


class Scene {
public:
    Scene();

    ~Scene();

    static Scene *currentScene; // This will probably suck for anything asynchronous
    std::string name = "Scene";
    bool shouldUpdate = true;
    bool shouldDraw = true;
    std::vector<Entity *> entities;
    std::vector<ECamera *> cameras;


    void Update(float dt);

    void Draw();
};


#endif //SCENE_H
