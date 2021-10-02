//
// Created by fer on 10/2/2021.
//

#ifndef TDOR_EPAWN_H
#define TDOR_EPAWN_H


#include "ECamera.h"

class EPawn : public ECamera {
public:
    float rotAngle = -PI / 2;

    void Update(float dt) override;

//    void Draw(Camera cam) override;
};


#endif //TDOR_EPAWN_H
