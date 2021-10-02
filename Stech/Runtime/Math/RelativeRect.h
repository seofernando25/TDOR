//
// Created by fer on 9/29/2021.
//

#ifndef RELATIVERECT_H
#define RELATIVERECT_H

#include <raylib.h>


class RelativeRect {
public:
    Vector2 parentDimensions{640, 480};
    Vector2 anchorMin{0, 0};
    Vector2 anchorMax{1., 1.};

    Rectangle GetRect() const;

    float GetX();

    float GetY();

    float GetW();

    float GetH();

    void SetX(float x);

    void SetY(float y);

    void SetW(float w);

    void SetH(float h);
};


#endif //RELATIVERECT_H
