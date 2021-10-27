//
// Created by fer on 10/2/2021.
//

#ifndef TDOR_EPAWN_H
#define TDOR_EPAWN_H


#include "Entity.h"

// Like a first person player, should probably work more on it
class EPawn : public Entity {
public:
    int mass = 100;
    int health = 100;
    float rotation = -PI / 2;
    float radius = 0.5f;
    float height = 1.0f;
};


#endif //TDOR_EPAWN_H
