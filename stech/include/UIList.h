//
// Created by fer on 9/27/2021.
//

#ifndef TDOR_UILIST_H
#define TDOR_UILIST_H

#include <string>
#include <vector>
#include "UIDrawable.h"

class UIList : public UIDrawable {
public:
    void draw() override;

    void update() override;

    UIList(const Font &font, std::vector<std::string> &elements);

    Font font;
    bool active = false;
    bool used = false;
    int currentSelected = 0;
    int maxWidth = 2;
    std::vector<std::string> &elements;

};


#endif //TDOR_UILIST_H
