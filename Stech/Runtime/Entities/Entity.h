//
// Created by fer on 9/30/2021.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>

#include "raylib.h"

/*
 * All entities should be derived from this
 * I'm not sure if they should be statically created on the editor
 * or on the lua VM
 */
class Entity {
public:
    Vector2 position{0, 0};
    float rotation = 0;
};


#endif //GAMEOBJECT_H
