//
// Created by fer on 9/27/2021.
//

#ifndef TDOR_UILIST_H
#define TDOR_UILIST_H

#include <string>
#include <vector>
#include "UIDrawable.h"
#include <raylib.h>

class UIList : public UIDrawable {
public:
    void Draw() override;

    void Update() override;

    UIList(const Font &font, std::vector<std::string> &elements);

    Font font;
    bool focused = false;
    unsigned int currentSelected = 0;
    unsigned int maxWidth = 2;
    std::vector<std::string> &elements;

};


#endif //TDOR_UILIST_H
