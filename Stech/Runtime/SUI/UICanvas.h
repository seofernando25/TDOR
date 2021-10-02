//
// Created by fer on 9/29/2021.
//

#ifndef TDOR_UICANVAS_H
#define TDOR_UICANVAS_H


#include "raylib.h"
#include "../../include/UIDrawable.h"
#include <vector>

#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480

#include "../Core/Component.h"

class Canvas : public Component {
public:
    std::vector<UIDrawable *> drawables;

    UICanvas();
};


#endif //TDOR_UICANVAS_H
