//
// Created by fer on 9/28/2021.
//

#include "SPanel.h"


UIPanel::UIPanel(float x, float y, float w, float h) {
    position.SetX(x);
    position.SetY(y);
    position.SetW(w);
    position.SetH(h);

}

void UIPanel::Draw() {
    DrawRectangle(position.GetX(), position.GetY(), width, height, WHITE);
    DrawRectangle(position.GetX() + borderW, position.GetY() + borderW, width - 2 * borderW, height - 2 * borderW,
                  BLACK);
}

void UIPanel::Update() {

}
