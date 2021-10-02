//
// Created by fer on 9/29/2021.
//

#include "RelativeRect.h"

Rectangle RelativeRect::GetRect() const {
    float tl_x = parentDimensions.x * anchorMin.x;
    float tl_y = parentDimensions.y * anchorMin.y;

    float br_x = parentDimensions.x * anchorMax.x;
    float br_y = parentDimensions.y * anchorMax.y;

    return Rectangle{tl_x, tl_y, br_x - tl_x, br_y - tl_y};
}

void RelativeRect::SetX(float x) {
    anchorMin.x = x / parentDimensions.x;
    anchorMax.x += x / parentDimensions.x;
}

void RelativeRect::SetY(float y) {
    anchorMin.y = y / parentDimensions.y;
    anchorMax.y += y / parentDimensions.y;
}

void RelativeRect::SetW(float w) {
    anchorMax.x = anchorMin.x + w / parentDimensions.x;
}

void RelativeRect::SetH(float h) {
    anchorMax.y = anchorMin.y + h / parentDimensions.y;
}

float RelativeRect::GetX() {
    return parentDimensions.x * anchorMin.x;
}

float RelativeRect::GetY() {
    return parentDimensions.y * anchorMin.y;
}

float RelativeRect::GetW() {
    return parentDimensions.x * anchorMax.x - GetX();
}

float RelativeRect::GetH() {
    return parentDimensions.y * anchorMax.y - GetY();
}
