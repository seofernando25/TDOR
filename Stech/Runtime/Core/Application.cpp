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
    SetWindowMinSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    SetExitKey(0);
    SetTargetFPS(60);

    // Creates the main render target
    renderTarget = LoadRenderTexture(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    SetTextureFilter(renderTarget.texture, TEXTURE_FILTER_POINT); // Make it look pixelated
}

void Application::Run() {
    bool wantsToClose = false;
    // Main game loop
    while (!wantsToClose) // Detect window close button or ESC key
    {
        wantsToClose = WindowShouldClose();

        // region Frame buffer scaling
        float scale = std::min((float) GetScreenWidth() / DEFAULT_WIDTH, (float) GetScreenHeight() / DEFAULT_HEIGHT);

        // Should we clamp the virtual mouse
        //Draws the game texture to the screen
        Rectangle srcRect{
                0.0f,
                0.0f,
                (float) renderTarget.texture.width,
                (float) -renderTarget.texture.height // Invert src vertically
        };
        Rectangle dstRect = {
                ((float) GetScreenWidth() - (DEFAULT_WIDTH * scale)) * 0.5f, // Centered x- left
                ((float) GetScreenHeight() - ((float) DEFAULT_HEIGHT * scale)) * 0.5f, // Center y-middle
                DEFAULT_WIDTH * scale,
                DEFAULT_HEIGHT * scale
        };
        // endregion

        // region Update
        float dt = GetFrameTime();
        for (const auto &scene: scenes) {
            if (scene->shouldUpdate)
                scene->Update(dt);
        }
        // endregion

        // region Draw to render target
        BeginTextureMode(renderTarget);
        ClearBackground(BLACK);

        for (const auto &scene: scenes) {
            if (scene->shouldDraw)
                scene->Draw();
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
