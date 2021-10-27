//
// Created by fer on 9/28/2021.
//

#ifndef TDOR_SPANEL_H
#define TDOR_SPANEL_H

#include <vector>
#include "raylib.h"
#include "SDrawable.h"

class SPanel : public SDrawable {
public:
    SPanel();
    void Update(float dt) override;
    void Draw(RelativeRect parent) override;

    bool clickable = false;
    std::vector<SDrawable*> children;
    int borderW = 6;
    Color borderColor = WHITE;

};

#endif //TDOR_SPANEL_H
