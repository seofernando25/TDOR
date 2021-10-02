//
// Created by fer on 9/27/2021.
//

#ifndef TDOR_UIDRAWABLE_H
#define TDOR_UIDRAWABLE_H


#include <raylib.h>
#include "../Runtime/Math/RelativeRect.h"

class UIDrawable {
public:
    void draw() { if (visible) draw(); };

    void update() { if (updatable) Update(); };

    bool visible = true;
    bool updatable = true;
    RelativeRect position;

    virtual void Draw() = 0;

    virtual void Update() = 0;
};


#endif //TDOR_UIDRAWABLE_H
