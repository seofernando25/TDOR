//
// Created by fer on 9/27/2021.
//

#ifndef TDOR_UIDRAWABLE_H
#define TDOR_UIDRAWABLE_H


#include <raylib.h>
#include "../Runtime/Math/RelativeRect.h"

class UIDrawable {
public:
    bool visible = true;
    bool updatable = true;
    RelativeRect position;

    virtual void Draw() {};

    virtual void Update() {};
};


#endif //TDOR_UIDRAWABLE_H
