//
// Created by fer on 10/2/2021.
//

#include "EBillboard.h"

void EBillboard::Draw(Camera cam) {
    DrawBillboard(cam, tex, position, size, WHITE);
}

EBillboard::EBillboard(const Texture2D &texture, float texSize) {
    tex = texture;
    size = texSize;
}

