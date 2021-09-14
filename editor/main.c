#include "raylib.h"
#include "raymath.h"

#include "l_config.h"
#include "c_actor.h"
#include "r_general.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "io_gdata.h"
#include <time.h>

// #define LUA_LIB
// #include "lua.h"
// #include "lauxlib.h"

#define WINDOW_DEFAULT_W 1280
#define WINDOW_DEFAULT_H 720

// Custom logging funtion
void LogCustom(int msgType, const char *text, va_list args)
{
    char timeStr[64] = {0};
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("[%s] ", timeStr);

    switch (msgType)
    {
    case LOG_INFO:
        printf("[INFO] : ");
        break;
    case LOG_ERROR:
        printf("[ERROR]: ");
        break;
    case LOG_WARNING:
        printf("[WARN] : ");
        break;
    case LOG_DEBUG:
        printf("[DEBUG]: ");
        break;
    default:
        break;
    }

    vprintf(text, args);
    printf("\n");
}

int main(int argc, char *argv[])
{
    // GData *gdata = CreateGDATA();
    // char *str1 = "Hi";
    // char *str2 = "Among us";
    // WriteToGDATA(gdata, "HI", sizeof(char) * strlen(str1), str1);
    // WriteToGDATA(gdata, "TEST", sizeof(char) * strlen(str2), str2);
    // SaveGDATA(gdata, "test.gdata");

    // Set the stdout to a file
    // freopen("log.txt", "w", stdout);
    // SetTraceLogCallback(LogCustom);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(WINDOW_DEFAULT_W, WINDOW_DEFAULT_H, "TDOR");
    SetWindowMinSize(512, 288);

    SetTargetFPS(60);
    // SetExitKey(0); // Prevents ESC from closing the window

    // Texture2D droog = LoadTexture("assets/droog.png");
    // Texture2D brick = LoadTexture("assets/brick.png");
    // SetTextureFilter(droog, TEXTURE_FILTER_POINT); // PixelArt texture filtering
    Camera camera = CreateDefaultCamera();

    SetCameraMode(camera, CAMERA_CUSTOM);

    // camera.target = (Vector3){0.0f, 0.0f, 0.0f};

    Wall wall;
    WallData data;
    data.height = 0;

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