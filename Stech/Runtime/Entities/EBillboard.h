//
// Created by fer on 10/2/2021.
//

#ifndef TDOR_EBILLBOARD_H
#define TDOR_EBILLBOARD_H


#include <raylib.h>
#include "Entity.h"

class EBillboard : public Entity {
public:
    explicit EBillboard(const Texture2D &tex, float size = 1);

    Texture2D tex;
    float size;

    void Draw(Camera cam) override;
};


#endif //TDOR_EBILLBOARD_H
