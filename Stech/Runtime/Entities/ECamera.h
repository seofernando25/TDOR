//
// Created by fer on 10/2/2021.
//

#ifndef TDOR_ECAMERA_H
#define TDOR_ECAMERA_H


#include "Entity.h"


class ECamera : public Entity {
public:
    ECamera();

    Vector3 cameraRelPosition = {0};
    Vector3 cameraRelTarget = {0, 0, -1};
    Vector3 cameraUp = {0, 1, 0};
    float cameraFovy = 90.f;
    CameraProjection cameraProjection = CAMERA_PERSPECTIVE;
    RenderTexture *renderTarget;

    void Render() const;
};

// TODO Implement these functions into ECamera class
//Vector3 CameraFoward(Camera *camera)
//{
//    return Vector3Subtract(camera->target, camera->position);
//}
//
//Vector3 CameraRight(Camera *camera)
//{
//    return Vector3CrossProduct(camera->up, CameraFoward(camera));
//}
//
//Vector3 CameraUp(Camera *camera)
//{
//    return Vector3CrossProduct(CameraFoward(camera), CameraRight(camera));
//}


#endif //TDOR_ECAMERA_H
