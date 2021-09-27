//
// Created by fer on 9/27/2021.
//

#ifndef TDOR_UIDRAWABLE_H
#define TDOR_UIDRAWABLE_H


#include <raylib.h>

class UIDrawable {
public:
    virtual void draw() = 0;

    virtual void update() = 0;

    Vector2 position = {0, 0};
};


#endif //TDOR_UIDRAWABLE_H
