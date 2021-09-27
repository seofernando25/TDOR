#include "raylib.h"
#include <algorithm>
#include "c_lua.h"
#include "r_gui.h"
#include <UILabel.h>
#include <UIList.h>


#define CMD_BUFFER_SIZE 255
#define VIRTUAL_WIDTH 640
#define VIRTUAL_HEIGHT 480


static char consoleInputEntry[CMD_BUFFER_SIZE] = "";

int main() {

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    const int screenWidth = VIRTUAL_WIDTH;
    const int screenHeight = VIRTUAL_HEIGHT;


    InitWindow(screenWidth, screenHeight, "TDOR Lua test");
    SetWindowMinSize(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
    SetExitKey(0);
    SetTargetFPS(60);

    // Creates the render target
    RenderTexture2D target = LoadRenderTexture(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT); // Make it look pixelated


    // Initial config and stuff

    currentStyle.fontSize = 32;
    currentStyle.font = LoadFont("data/core/fonts/DTM-Mono.otf");
    UILabel my_label(currentStyle.font, "Hello amongus");
    std::vector<std::string> list_elems{"iTEM 1", "IteM 2", "TEST 3", "Something 5", "other thing", "wow what??",
                                        "le litem", "Pog champ", "pong poing"};
    UIList my_list(currentStyle.font, list_elems);
    my_list.position.x = 150;
    my_list.maxWidth = 2;
    currentStyle.fontColor = {255, 0, 0, 255};
    // Initializes lua

    lua_State *L = luaL_newstate();
    luaL_openlibs(L); // We probably should not open sensitive libraries such as os

    lua_pushcfunction(L, luaDrawRect);
    lua_setglobal(L, "draw_rect");
    lua_pushcfunction(L, luaDrawText);
    lua_setglobal(L, "draw_text");

    // NOTE Set the executable working directory to the root
    // of the build folder
    int error = luaL_dofile(L, "./data/core/lualib/init.lua");
    if (error == LUA_OK)
    {
        printf("Lua initialized\n");
    }
    else
    {
        const char *error_msg = lua_tostring(L, -1);
        printf("%s\n", error_msg);
        // Can't really log to console if this fails
        //ConsoleLog(L, lua_tostring(L, -1));
    }

    int c = 0;
    bool wantsToClose = false;
    // Main game loop
    while (!wantsToClose) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        wantsToClose = WindowShouldClose();

        // region Frame buffer scaling
        float scale = std::min((float) GetScreenWidth() / VIRTUAL_WIDTH, (float) GetScreenHeight() / VIRTUAL_HEIGHT);

        // Update virtual mouse (clamped mouse value behind game screen)
        Vector2 mouse = GetMousePosition();
        Vector2 virtualMouse = {0};
        virtualMouse.x = (mouse.x - ((float) GetScreenWidth() - (VIRTUAL_WIDTH * scale)) * 0.5f) / scale;
        virtualMouse.y = (mouse.y - ((float) GetScreenHeight() - (VIRTUAL_HEIGHT * scale)) * 0.5f) / scale;
        // Should we clamp the virtual mouse
        //Draws the game texture to the screen
        Rectangle srcRect{
                0.0f,
                0.0f,
                (float) target.texture.width,
                (float) -target.texture.height // Invert src vertically
        };
        Rectangle dstRect = {
                ((float) GetScreenWidth() - (VIRTUAL_WIDTH * scale)) * 0.5f, // Centered x- left
                ((float) GetScreenHeight() - ((float) VIRTUAL_HEIGHT * scale)) * 0.5f, // Center y-middle
                VIRTUAL_WIDTH * scale,
                VIRTUAL_HEIGHT * scale
        };


        // endregion

        if (IsKeyPressed(KEY_GRAVE)) {
            StackDump(L);
        }

        //----------------------------------------------------------------------------------
        // Draw to target
        //----------------------------------------------------------------------------------
        BeginTextureMode(target);
        ClearBackground(GRAY);

        // UI Stuff

        // Console stuff
        // TODO Move console to UI itself

        DrawText(">", 0, 0, (int) currentStyle.fontSize, BLACK);

        if (SInputLine(0, 0, consoleInputEntry, 255, true)) {
            ConsoleWrite(L, "]");
            ConsoleLog(L, consoleInputEntry);
            DoString(L, consoleInputEntry);
            consoleInputEntry[0] = '\0';
        }

        const char *screenBuf = GetConsoleBuffer(L);
        SDrawText(screenBuf, 0, currentStyle.fontSize, ALIGN_START, ALIGN_START);

        char luaStackSize[32] = "Lua stack: ";
        snprintf(luaStackSize + strlen(luaStackSize), 32 - strlen(luaStackSize), "%d", lua_gettop(L));
        SDrawText(luaStackSize, 0, screenHeight - currentStyle.fontSize, ALIGN_START, ALIGN_START);
//        DoString(L, "draw()");

        STextBox("This text should be perfectly centered", VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 2, 16, ALIGN_CENTER,
                 ALIGN_CENTER);
        const char *elems[3] = {"Value 1", "Value 2", "Value 3"};

        SDrawBox({
                         50,
                         50,
                         strlen(elems[0]) * currentStyle.fontSize,
                         3 * currentStyle.fontSize},
                 GetContrastingColor(currentStyle.fontColor),
                 currentStyle.accentColor);
        SVList(50, 50, (char **) elems, 3, &c);

//        my_label.draw();
        my_list.draw();
        EndTextureMode();
        // region Draw to frame buffer

        BeginDrawing();
        ClearBackground(BLACK); // Clear screen background
        DrawTexturePro(target.texture, srcRect, dstRect,
                       {0, 0}, 0.0f, WHITE);
        DrawFPS(0, 0);
        EndDrawing();

        // endregion
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    lua_close(L);
    return 0;
}