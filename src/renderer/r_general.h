// General render functions

#ifndef R_GENERAL_H
#define R_GENERAL_H

#include "c_wall.h"
#include "c_walldata.h"
#include "raylib.h"

Matrix getTransformMatrix(Transform transform)
{
    Matrix matrix = MatrixIdentity();

    matrix = MatrixMultiply(matrix, MatrixScale(transform.scale.x, transform.scale.y, transform.scale.z));                       // Scale
    matrix = MatrixMultiply(matrix, QuaternionToMatrix(transform.rotation));                                                     // Rotate
    matrix = MatrixMultiply(matrix, MatrixTranslate(transform.translation.x, transform.translation.y, transform.translation.z)); // Translate
    return matrix;
}

Camera CreateDefaultCamera()
{
    Camera camera = {0};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.position = (Vector3){0.0f, 1.0f, 0.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.fovy = 90.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    return camera;
}

// This needs to be worked on
void DrawWall(Mesh wallMesh, Material material, Transform wallTransform, Vector2 p1, Vector2 p2)
{
    Vector3 wallCenter = Vector3Add(Vector3Scale((Vector3){p1.x, 0, p1.y}, 0.5f), Vector3Scale((Vector3){p2.x, 0, p2.y}, 0.5f));
    wallTransform.translation = wallCenter;
    wallTransform.translation.y = 0.5f;
    Vector2 wallDistanceDelta = Vector2Subtract(p1, p2);
    float wallAngle = atan2(wallDistanceDelta.y, wallDistanceDelta.x);
    wallTransform.scale.x = Vector2Length(wallDistanceDelta);

    wallTransform.rotation = QuaternionFromEuler(PI / 2, -wallAngle, 0);
    DrawMesh(wallMesh, material, getTransformMatrix(wallTransform));
    wallTransform.rotation = QuaternionFromEuler(-PI / 2, -wallAngle, 0);
    DrawMesh(wallMesh, material, getTransformMatrix(wallTransform));
}

#endif