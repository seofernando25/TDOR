//
// Created by fer on 9/28/2021.
//

#include "SPanel.h"

SPanel::SPanel() {
    relativeRect.SetX(10);
    relativeRect.SetY(10);
    relativeRect.SetW(580);
    relativeRect.SetH(150);
}

void SPanel::Draw(RelativeRect parent) {
    if(!visible)
        return;

    RelativeRect rect = parent.ChildTransform(relativeRect);

    Rectangle inner = rect.GetRect();

    // Draw Inner Panel
    inner.x += borderW;
    inner.y += borderW;
    inner.width -= borderW * 2;
    inner.height -= borderW * 2;
    DrawRectangleRec(rect.GetRect(), borderColor);
    DrawRectangleRec(inner, BLACK);

    // Update the rect box for children
    rect.SetX(inner.x);
    rect.SetY(inner.y);
    rect.SetW(inner.width);
    rect.SetH(inner.height);

    // Update all children to sort fit in the channel
    for (const auto &child : children){
        child->Draw(rect);
    }
}

void SPanel::Update(float dt) {
    for (const auto &child : children){
        child->Update(dt);
    }
}



