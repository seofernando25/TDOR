
#include "raylib.h"
#include "raymath.h"

Vector3 CameraFoward(Camera *camera)
{
    return Vector3Subtract(camera->target, camera->position);
}

Vector3 CameraRight(Camera *camera)
{
    return Vector3CrossProduct(camera->up, CameraFoward(camera));
}

Vector3 CameraUp(Camera *camera)
{
    return Vector3CrossProduct(CameraFoward(camera), CameraRight(camera));
}