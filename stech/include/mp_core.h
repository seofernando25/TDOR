
#pragma once

#include "raylib.h"

typedef struct LineRef {
    unsigned startVert;
    unsigned endVert;
} LineRef;

typedef struct Wall {
    LineRef line;
    int wallDataIndex;
} Wall;

typedef struct WallData {
    Texture2D texture;
    float height;
} WallData;

typedef struct MapGeometry {
    unsigned wallCnt;
    unsigned vertCnt;
    LineRef *walls;
    Vector2 *vertices;
} MapGeometry;