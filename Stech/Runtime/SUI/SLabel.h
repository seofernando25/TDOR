//
// Created by fer on 9/27/2021.
//

#ifndef TDOR_SLABEL_H
#define TDOR_SLABEL_H

#include "SDrawable.h"
#include <string>
#include "raylib.h"

#define DEFAULT_TEXT_SIZE 32

class SLabel : public SDrawable {
public:
    SLabel(const Font &font, const std::string &text);



    Font font;
    Color fontColor = {255, 255, 255, 255};
    std::string text;
    int size = DEFAULT_TEXT_SIZE; // Using the default values a screen should fit 40x15 characters
    bool lineWrap = true;
    int maxLineWidth = 40;

};


#endif //TDOR_SLABEL_H
