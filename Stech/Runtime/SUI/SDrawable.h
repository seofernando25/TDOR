//
// Created by fer on 9/27/2021.
//

#ifndef TDOR_SDRAWABLE_H
#define TDOR_SDRAWABLE_H


#include <Core/Application.h>
#include <raylib.h>
#include "../Runtime/Math/RelativeRect.h"

#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480

class SDrawable {
public:
    static SDrawable* lastClicked;
    bool visible = true;
    bool clickable = true;
    bool updatable = true;
    bool focused = false;
    RelativeRect relativeRect{ DEFAULT_WIDTH, DEFAULT_HEIGHT, 0,0,1,1};

    virtual void Draw(RelativeRect parentRect) {};
    virtual void Update(float dt) {};
    virtual void OnClick() {};
};



#endif //TDOR_SDRAWABLE_H
