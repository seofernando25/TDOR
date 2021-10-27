//
// Created by fer on 9/30/2021.
//

#ifndef SCENE_H
#define SCENE_H


#include <string>
#include <vector>
#include <raylib.h>
#include <Entities/Entity.h>
class SDrawable;
#include <SUI/SDrawable.h>
class Thinker;
#include <Core/Thinker.h>
#include "Wall.h"
#include "SectorDef.h"

// Map definition
class LevelStatic {
public:
    std::vector<Vector2> vertex;
    std::vector<Vector2> walls; // List of N walls from (wall_start, wall_end)

//    std::vector<SectorDef> sectors;
//    Camera* mainCamera;
//    std::string name = "Scene";
//    std::vector<Entity *> entities;
//    std::vector<SDrawable *> uiEntities;
//    std::vector<Thinker*> thinkers;
//    void Update(float dt);
//    void Render(RenderTexture target);
//private:
//    void UpdateUI(RenderTexture target);
};


#endif //SCENE_H
