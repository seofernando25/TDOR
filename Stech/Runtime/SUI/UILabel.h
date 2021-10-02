//
// Created by fer on 9/27/2021.
//

#ifndef TDOR_UILABEL_H
#define TDOR_UILABEL_H

#include "UIDrawable.h"
#include <string>
#include "raylib.h"

#define DEFAULT_TEXT_SIZE 32

class UILabel : public UIDrawable {
public:
    UILabel(const Font &font, const std::string &text);

    void Draw() override;

    void Update() override;

    Font font;
    Color fontColor = {255, 255, 255, 255};
    std::string text;
    int size = DEFAULT_TEXT_SIZE; // Using the default values a screen should fit 40x15 characters
    bool lineWrap = true;
    int maxLineWidth = 40;

};


#endif //TDOR_UILABEL_H
