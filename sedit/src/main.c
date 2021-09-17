#include "raylib.h"

#include "c_lua.h"

#define CMD_BUFFER_SIZE 255
#define FONT_SIZE 8

bool SInputLine(int x, int y, char *text, int buffSize, bool editMode)
{
    if (editMode)
    {
        int key = GetCharPressed(); // Returns codepoint as Unicode
        int keyCount = (int)strlen(text);
        bool bufferNotFull = keyCount < (buffSize - 1);
        // Only allow keys in range [32..125]
        if (bufferNotFull && key >= 32)
        {
            text[keyCount] = key;
            keyCount++;
            text[keyCount] = '\0';
        }
        else if (buffSize > 0 && IsKeyPressed(KEY_BACKSPACE))
        {
            keyCount--;
            text[keyCount] = '\0';
        }
    }
    DrawText(text, x, y, FONT_SIZE, BLACK);
    return IsKeyPressed(KEY_ENTER);
}

static char consoleInputEntry[CMD_BUFFER_SIZE] = "";

int main()
{

    int screenWidth = 690;
    int screenHeight = 560;

    InitWindow(screenWidth, screenHeight, "TDOR Lua test");
    SetExitKey(0);
    SetTargetFPS(60);

    // Initializes lua

    lua_State *L = luaL_newstate();
    luaL_openlibs(L); // We probably should not open sensitive libraries such as os

    lua_pushcfunction(L, luaDrawRect);
    lua_setglobal(L, "draw_rect");
    lua_pushcfunction(L, luaDrawText);
    lua_setglobal(L, "draw_text");

    int error = luaL_dofile(L, "data/core/lualib/init.lua");
    if (error == LUA_OK)
    {
        printf("Lua initialized\n");
    }
    else
    {
        ConsoleLog(L, lua_tostring(L, -1));
    }

    bool wantsToClose = false;
    // Main game loop
    while (!wantsToClose) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        wantsToClose = WindowShouldClose();

        if (IsKeyPressed(KEY_GRAVE))
        {
            StackDump(L);
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(WHITE);

        // UI Stuff

        // Console stuff
        // TODO Move console to UI itself

        DrawText(">", 0, 0, FONT_SIZE, BLACK);
        if (SInputLine(FONT_SIZE, 0, consoleInputEntry, 255, true))
        {
            ConsoleWrite(L, "]");
            ConsoleLog(L, consoleInputEntry);
            DoString(L, consoleInputEntry);
            consoleInputEntry[0] = '\0';
        }

        const char *screenBuf = GetConsoleBuffer(L);
        DrawText(screenBuf, 0, FONT_SIZE, FONT_SIZE, BLACK);

        char luaStackSize[32];
        sprintf(luaStackSize, "%d", lua_gettop(L));
        DrawText(luaStackSize, screenWidth - 3 * FONT_SIZE, screenHeight - FONT_SIZE, FONT_SIZE, BLACK);

        DrawText("Lua stack: ", 0, screenHeight - FONT_SIZE, FONT_SIZE, BLACK);
        DoString(L, "draw()");

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    lua_close(L);
    return 0;
}