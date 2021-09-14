#pragma once

#include "c_actor.h"
#include "c_wall.h"
#include "raylib.h"

struct Level
{
    Actor *actors;
    Wall *wallLines;
    Vector2 *wallVertices;
};
