//
// Created by fer on 9/30/2021.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>

#include "raylib.h"
#include <unordered_map>
#include <typeinfo>

/*
 * All entities should be derived from this
 */
class Entity {
public:
    Vector3 position{0, 0, 0};

    virtual void Update(float dt) {};

    virtual void Draw(Camera cam) {};
};


#endif //GAMEOBJECT_H
