#pragma once

#include "raylib.h"

typedef struct Actor
{
    Transform transform;
    unsigned int actorID;
    unsigned int actorType;
} Actor;