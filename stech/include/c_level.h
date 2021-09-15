#pragma once

#include "c_actor.h"
#include "mp_core.h"
#include "raylib.h"

struct Level
{
    Actor *actors;
    Wall *wallLines;
    Vector2 *wallVertices;
};
