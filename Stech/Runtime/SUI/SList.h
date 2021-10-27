//
// Created by fer on 9/27/2021.
//

#ifndef TDOR_SLIST_H
#define TDOR_SLIST_H

#include <string>
#include <vector>
#include "SDrawable.h"
#include <raylib.h>

class SList : public SDrawable {
public:
    SList(const Font &font, std::vector<std::string> &elements);
    void Draw(RelativeRect parentRect) override;
    void Update(float dt);


    Font font;
    unsigned int currentSelected = 0;

    void OnClick() override;


    unsigned int maxWidth = 2;
    std::vector<std::string> &elements;
};


#endif //TDOR_SLIST_H
