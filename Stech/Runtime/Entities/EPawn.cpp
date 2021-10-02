//
// Created by fer on 10/2/2021.
//

#include "EPawn.h"

void EPawn::Update(float dt) {
    int moveZ = IsKeyDown(KEY_W) - IsKeyDown(KEY_S);
    int moveX = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);

    int rotY = IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT);
    rotAngle += rotY * dt;
    cameraRelTarget = {cosf(rotAngle), 0, sinf(rotAngle)};

    position.x += dt * (moveX * sin(-rotAngle) + moveZ * cos(rotAngle));
    position.z += dt * (moveX * cos(rotAngle) + moveZ * sin(rotAngle));
}

