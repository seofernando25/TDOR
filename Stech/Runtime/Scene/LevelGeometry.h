//
// Created by fer on 9/30/2021.
//

#ifndef SCENE_H
#define SCENE_H


#include "raylib.h"
#include <vector>

// Map definition
class LevelGeometry {
public:
    std::vector<Vector2> vertex;
    // std::vector<SectorDef> sectorsDef;
    // Lists of walls may represent sectors
    // std::vector<std::vector<int>> sectors;
    std::vector<Vector2> lines; // points to two vertexes

    bool RemoveVertex(int vertexIndex);
};




#endif //SCENE_H
