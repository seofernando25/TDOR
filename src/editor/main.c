#include "raylib.h"
#include "raymath.h"

#include "c_actor.h"
#include "r_general.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define WINDOW_DEFAULT_W 1280
#define WINDOW_DEFAULT_H 720

int main(int argc, char *argv[])
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(WINDOW_DEFAULT_W, WINDOW_DEFAULT_H, "TDOR");
    SetWindowMinSize(512, 288);

    SetTargetFPS(60);
    // SetExitKey(0); // Prevents ESC from closing the window

    Texture2D droog = LoadTexture("assets/droog.png");
    Texture2D brick = LoadTexture("assets/brick.png");
    SetTextureFilter(droog, TEXTURE_FILTER_POINT); // PixelArt texture filtering
    Camera camera = CreateDefaultCamera();

    SetCameraMode(camera, CAMERA_CUSTOM);

    // camera.target = (Vector3){0.0f, 0.0f, 0.0f};

    Wall wall;
    WallData data;
    data.height = 0;
    data.texture = droog;
    // wall.data = &data;
    Vector2 p1 = (Vector2){0, 0};
    Vector2 p2 = (Vector2){5, 2};

    wall.line.startVertex = 0;
    wall.line.endVertex = 1;

    Mesh wallMesh = GenMeshPlane(1, 1, 1, 1);
    Transform wallTransform = {0};
    wallTransform.scale = (Vector3){1, 1, 1};
    Material defaultMat = LoadMaterialDefault();
    while (!WindowShouldClose())
    {
        // Orbit arround center
        float time = GetTime();
        float angle = time * 0.5f;
        p2 = (Vector2){cosf(-angle * 2.0f) * 2.0f, sinf(-angle * 2.0f) * 2.0f};
        camera.position.x = cos(angle) * 5.0f;
        camera.position.y = 2.0f;
        camera.position.z = sin(angle) * 5.0f;
        camera.target = (Vector3){0.0f, 1.0f, 0.0f};
        UpdateCamera(&camera);

        // Stuff
        BeginDrawing();
        ClearBackground(GRAY); // Clear screen background

        // Draw 3D stuff
        BeginMode3D(camera);
        DrawGrid(10, 1.0);

        Vector3 cameraDirection = Vector3Normalize(Vector3Subtract(camera.position, wallTransform.translation));
        Vector3 cameraRight = Vector3Normalize(Vector3CrossProduct(camera.up, cameraDirection));
        Vector3 cameraUp = Vector3CrossProduct(cameraDirection, cameraRight);
        // wallTransform.scale.x = 3 + sin(time) * 2.0f;

        // region Wall rendering
        DrawWall(wallMesh, defaultMat, wallTransform, p1, p2);

        DrawSphere((Vector3){p1.x, 0.f, p1.y}, 0.2f, GREEN);
        DrawSphere((Vector3){p1.x, 1.f, p1.y}, 0.2f, GREEN);
        DrawSphere((Vector3){p2.x, 0.f, p2.y}, 0.2f, GREEN);
        DrawSphere((Vector3){p2.x, 1.f, p2.y}, 0.2f, GREEN);
        // endregion
        EndMode3D();

        DrawFPS(0, 0);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}