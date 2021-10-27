//
// Created by fer on 9/27/2021.
//

#include "UIList.h"

#define LIST_FONT_SIZE 32

void UIList::Draw() {
    if (!visible)
        return;

    for (unsigned int item_i = 0; item_i < elements.size(); ++item_i) {
        unsigned int h = item_i / maxWidth;
        Vector2 offset{(float) (item_i % maxWidth * 10) * LIST_FONT_SIZE, (float) h * LIST_FONT_SIZE};
        Vector2 pos{position.GetX() + offset.x, position.GetY() + offset.y};

        if (item_i == currentSelected) {
            // Draw *
            DrawTextEx(
                    font,
                    "*",
                    pos,
                    LIST_FONT_SIZE,
                    0,
                    {255, 255, 255, 255}
            );
        }

        DrawTextEx(
                font,
                elements.at(item_i).c_str(),
                {pos.x + LIST_FONT_SIZE, pos.y},
                LIST_FONT_SIZE,
                0,
                {255, 255, 255, 255}
        );

    }
}

void UIList::Update() {
    if (!focused)
        return;

    int change = -(int) IsKeyPressed(KEY_LEFT) + (int) IsKeyPressed(KEY_RIGHT)
                 - maxWidth * (int) IsKeyPressed(KEY_UP) + maxWidth * (int) IsKeyPressed(KEY_DOWN);
    int t = (int) currentSelected + change;
    t -= (t >= (int) elements.size()) * t; // Resets to zero if exceeded
    t += (t < 0) * (-t + elements.size() - 1); // Resets to max if less than zero
    currentSelected = (unsigned int) t;
}

UIList::UIList(const Font &font, std::vector<std::string> &elements) : font(font), elements(elements) {
    this->font = font;
    this->elements = elements;
}


