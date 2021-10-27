//
// Created by fer on 9/30/2021.
//

#include <raylib.h>
#include "Application.h"

Application *Application::instance = nullptr;

Application::Application(const std::string &name, int window_w, int window_h) {
    instance = this;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(window_w, window_h, name.c_str());
    SetWindowMinSize(window_w/2, window_h/2);
    SetExitKey(0);
    SetTargetFPS(60);

    // Creates the main render target
    renderTarget = LoadRenderTexture(window_w, window_h);
    SetTextureFilter(renderTarget.texture, TEXTURE_FILTER_POINT); // Make it look pixelated
}

void Application::Run() {
    bool wantsToClose = false;
    // Main game loop
    while (!wantsToClose) // Detect window close button or ESC key
    {
        wantsToClose = WindowShouldClose();

        // region Frame buffer scaling
        float scale = std::min((float) GetScreenWidth() / renderTarget.texture.width, (float) GetScreenHeight() / renderTarget.texture.height);
        Rectangle srcRect{
                0.0f,
                0.0f,
                (float) renderTarget.texture.width,
                (float) -renderTarget.texture.height // Invert src vertically
        };
        Rectangle dstRect = {
                ((float) GetScreenWidth() - (renderTarget.texture.width * scale)) * 0.5f, // Centered x- left
                ((float) GetScreenHeight() - ((float) renderTarget.texture.height * scale)) * 0.5f, // Center y-middle
                renderTarget.texture.width * scale,
                renderTarget.texture.height * scale
        };
        // endregion


        // region Update
        float dt = GetFrameTime();
        for (const auto &scene: scenes) {
//            scene->Update(dt);
        }
        // endregion

        // region Draw to render target
        BeginTextureMode(renderTarget);
        ClearBackground(BLACK);

        for (const auto &scene: scenes) {
            // TODO what if we have no cameras? How do we specify that we want to render n player or certain camera?
//            scene->Render(renderTarget);
        }
        EndTextureMode();
        // endregion

        // region Draw target to main frame buffer
        BeginDrawing();
        ClearBackground(GRAY); // Clear screen background
        DrawTexturePro(renderTarget.texture, srcRect, dstRect,
                       {0, 0}, 0.0f, WHITE);
        EndDrawing();
        // endregion
    }

    CloseWindow();
}

Vector2 Application::GetVirtualMousePosition() {
    float scale = std::min((float) GetScreenWidth() / renderTarget.texture.width, (float) GetScreenHeight() / renderTarget.texture.height);
    Vector2 mouse = GetMousePosition();
    Vector2 virtualMouse = {0};
    virtualMouse.x = (mouse.x - (GetScreenWidth() - (renderTarget.texture.width * scale)) * 0.5f) / scale;
    virtualMouse.y = (mouse.y - (GetScreenHeight() - (renderTarget.texture.height * scale)) * 0.5f) / scale;
    return virtualMouse;
}
