//
// Created by fer on 9/30/2021.
//

#ifndef THINKER_H
#define THINKER_H

#include <string>
#include "Scene/LevelGeometry.h"

class LevelGeometry;
/*
 * A scene can have many thinkers, they act as "MonoBehaviours" if you will
 * but are not attached to any entity. On the other hand, they can "find" entities
 * and be responsible for a certain one for example
 */
class Thinker {
public:
    // TODO ThinkerScript class that uses lua to think
    bool wantsToBeRemoved = false;
    int tickMod = 1; // Run this every tick (tick%tickMod == 0)

    virtual void OnAdded(LevelGeometry* scene) {};
    virtual void Tick(LevelGeometry* scene) {};
    virtual void OnRemoved(LevelGeometry* scene) {};
};


#endif //THINKER_H
