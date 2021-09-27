//
// Created by fer on 9/27/2021.
//

#include "UIList.h"

void UIList::draw() {
    for (int item_i = 0; item_i < elements.size(); ++item_i) {
        int h = item_i / maxWidth;
        Vector2 offset{(float) (item_i % maxWidth * 10) * 16.f, (float) h * 32.f};
        Vector2 pos{position.x + offset.x, position.y + offset.y};

        DrawTextEx(
                font,
                elements.at(item_i).c_str(),
                pos,
                32,
                0,
                {255, 255, 255, 255}
        );

    }
}

void UIList::update() {

}

UIList::UIList(const Font &font, std::vector<std::string> &elements) : font(font), elements(elements) {
    this->font = font;
    this->elements = elements;
}


