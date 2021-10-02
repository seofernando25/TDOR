//
// Created by fer on 9/28/2021.
//

#ifndef TDOR_UIPANEL_H
#define TDOR_UIPANEL_H

#include "raylib.h"
#include "UIDrawable.h"

class UIPanel : public UIDrawable {
public:
    UIPanel(float x, float y, float w, float h);


    void Draw() override;

    void Update() override;

    int width = 580;
    int height = 150;
    int borderW = 6;;
};

#endif //TDOR_UIPANEL_H
