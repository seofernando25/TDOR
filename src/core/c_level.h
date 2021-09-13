

#ifndef C_LEVEL_H
#define C_LEVEL_H

#include "c_actor.h"
#include "c_wall.h"
#include "raylib.h"

struct Level
{
    Actor *actors;
    Wall *wallLines;
    Vector2 *wallVertices;
};
