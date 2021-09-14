#include "raylib.h"
#include <math.h>
#include <stdio.h>

#define VIRTUAL_WIDTH 480
#define VIRTUAL_HEIGHT 360

#define WINDOW_HEIGHT 450
#define WINDOW_WIDTH 800

#define WALL_STEP 10
#define FLOOR_STEP 20

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

// Clamp Vector2 value with min and max and return a new vector2
// NOTE: Required for virtual mouse, to clamp inside virtual game size
// TODO: Move to a better place
Vector2 ClampValue(Vector2 value, Vector2 min, Vector2 max)
{
    Vector2 result = value;
    result.x = (result.x > max.x) ? max.x : result.x;
    result.x = (result.x < min.x) ? min.x : result.x;
    result.y = (result.y > max.y) ? max.y : result.y;
    result.y = (result.y < min.y) ? min.y : result.y;
    return result;
}

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "TDOR");
    SetWindowMinSize(320, 240);

    RenderTexture2D target = LoadRenderTexture(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);

    SetTargetFPS(60);

    Vector2 playerPosition = (Vector2){1, 2};
    float playerRotation = 0;

    int mapData[4][5] =
        {
            {0, 1, 1, 1, 0},
            {1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1},
            {0, 1, 1, 1, 0},
        };

    int mapWidth = 5;
    int mapHeight = 4;

    int wallMid = 360 / 2;
    int screenMid = 480 / 2;

    const int rayCount = VIRTUAL_WIDTH / WALL_STEP;

    float fov = PI / 2;

    Vector2 wallStart = {3, 0};
    Vector2 wallEnd = {4, 2};
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC
    {
        // Update
        //----------------------------------------------------------------------------------
        // Compute required framebuffer scaling
        float scale = min((float)GetScreenWidth() / VIRTUAL_WIDTH, (float)GetScreenHeight() / VIRTUAL_HEIGHT);

        // Update virtual mouse (clamped mouse value behind game screen)
        Vector2 mouse = GetMousePosition();
        Vector2 virtualMouse = {0};
        virtualMouse.x = (mouse.x - (GetScreenWidth() - (VIRTUAL_WIDTH * scale)) * 0.5f) / scale;
        virtualMouse.y = (mouse.y - (GetScreenHeight() - (VIRTUAL_HEIGHT * scale)) * 0.5f) / scale;
        virtualMouse = ClampValue(virtualMouse, (Vector2){0, 0}, (Vector2){(float)VIRTUAL_WIDTH, (float)VIRTUAL_HEIGHT});

        // Update player distance if the player presses w it goes closer to the wall
        // if it presses s it goes away
        if (IsKeyDown(KEY_W))
        {
            playerPosition.x += 0.01f;
        }
        if (IsKeyDown(KEY_S))
        {
            playerPosition.x -= 0.01f;
        }
        if (IsKeyDown(KEY_A))
        {
            playerPosition.y -= 0.01f;
        }
        if (IsKeyDown(KEY_D))
        {
            playerPosition.y += 0.01f;
        }

        // Update player rotation
        if (IsKeyDown(KEY_LEFT))
        {
            playerRotation -= 0.01f;
        }
        if (IsKeyDown(KEY_RIGHT))
        {
            playerRotation += 0.01f;
        }

        BeginTextureMode(target);

        ClearBackground(GRAY); // Clear render texture background color

        // Main

        // Draw the floor starting from the middle of the screen
        for (int y = VIRTUAL_HEIGHT / 2; y < VIRTUAL_HEIGHT; y += FLOOR_STEP)
        {
            float col = (float)y / VIRTUAL_HEIGHT;
            Color floorColor = (Color){(int)(col * 255), (int)(col * 255), (int)(col * 255), 255};
            DrawRectangle(0, y, VIRTUAL_WIDTH, FLOOR_STEP, floorColor);
        }

        for (int x = 0; x < rayCount; x++)
        {
            float angleCoef = x / (float)rayCount;
            float realRayAngle = fov * angleCoef - fov / 2.0f;
            realRayAngle += playerRotation;

            // Take the ray angle and add the player angle
            float rayDirX = cosf(realRayAngle);
            float rayDirY = sinf(realRayAngle);
            if (fabs(rayDirX) < 0.001f)
                rayDirX = 0.001f;
            if (fabs(rayDirY) < 0.001f)
                rayDirY = 0.001f;

            float sideDistX = 0;
            float sideDistY = 0;

            float deltaDistDx = fabs(1.0f / rayDirX);
            float deltaDistDy = fabs(1.0f / rayDirY);

            int stepX = 0;
            int stepY = 0;

            int mapX = (int)playerPosition.x;
            int mapY = (int)playerPosition.y;

            if (rayDirX < 0)
            {
                stepX = -1;
                sideDistX = (playerPosition.x - (int)playerPosition.x) * deltaDistDx;
            }
            else
            {
                stepX = 1;
                sideDistX = ((int)playerPosition.x + 1.0f - playerPosition.x) * deltaDistDx;
            }
            if (rayDirY < 0)
            {
                stepY = -1;
                sideDistY = (playerPosition.y - (int)playerPosition.y) * deltaDistDy;
            }
            else
            {
                stepY = 1;
                sideDistY = ((int)playerPosition.y + 1.0f - playerPosition.y) * deltaDistDy;
            }

            int steps = 0;
            while (steps++ < 100)
            {
                int side = 0;
                if (sideDistX < sideDistY)
                {
                    sideDistX += deltaDistDx;
                    mapX += stepX;
                }
                else
                {
                    sideDistY += deltaDistDy;
                    mapY += stepY;
                    side = 1;
                }

                if (mapData[mapY][mapX])
                {
                    float wallDist;
                    if (side == 0)
                        wallDist = (mapX - playerPosition.x + (1 - stepX) / 2) / rayDirX;
                    else
                        wallDist = (mapY - playerPosition.y + (1 - stepY) / 2) / rayDirY;
                    // Corrected wall height to prevent fish eye effect
                    float intercepX = playerPosition.x + rayDirX * wallDist;
                    float intercepY = playerPosition.y + rayDirY * wallDist;
                    float dx = (intercepX - playerPosition.x);
                    float dy = (intercepY - playerPosition.y);

                    float projectedDistance = dx * cosf(playerRotation) + dy * sinf(playerRotation);
                    float wallHeight = (VIRTUAL_HEIGHT / projectedDistance);
                    Color wallColor = (Color){(int)(255 - (wallDist / 5) * 255), (int)(255 - (wallDist / 5) * 255), (int)(255 - (wallDist / 5) * 255), 255};
                    DrawRectangle(x * WALL_STEP, (VIRTUAL_HEIGHT / 2) - (wallHeight / 2), WALL_STEP, wallHeight, wallColor);
                    break;
                }
            }
        }

        // Prints the player position
        DrawText("Player position:", 10, 10, 20, WHITE);
        DrawText(TextFormat("(%.2f, %.2f)", playerPosition.x, playerPosition.y), 10, 30, 20, WHITE);

        EndTextureMode();

        BeginDrawing();
        DrawFPS(0, 0);
        ClearBackground(BLACK); // Clear screen background

        //Draws the game texture to the screen
        DrawTexturePro(target.texture, (Rectangle){0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height},
                       (Rectangle){(GetScreenWidth() - ((float)VIRTUAL_WIDTH * scale)) * 0.5f, (GetScreenHeight() - ((float)VIRTUAL_HEIGHT * scale)) * 0.5f,
                                   (float)VIRTUAL_WIDTH * scale, (float)VIRTUAL_HEIGHT * scale},
                       (Vector2){0, 0}, 0.0f, WHITE);
        EndDrawing();
        //--------------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadRenderTexture(target); // Unload render texture

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}