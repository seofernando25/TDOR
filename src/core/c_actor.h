// Defines the base actor class
// eg: anything that can be placed in the world

#ifndef C_ACTOR_H
#define C_ACTOR_H

#include "raylib.h"

typedef struct Actor
{
    Transform transform;
    unsigned int actorID;
    unsigned int actorType;
} Actor;

#endif