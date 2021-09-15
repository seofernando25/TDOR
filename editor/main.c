#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_RICONS

#include "r_raygui.h"

#undef RAYGUI_IMPLEMENTATION

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#define CMD_BUFFER_SIZE 255
#define FONT_SIZE 24

bool SInputLine(int x, int y, char *text, int buffSize, bool editMode) {
    if (editMode) {
        int key = GetCharPressed();      // Returns codepoint as Unicode
        int keyCount = (int) strlen(text);
        bool bufferNotFull = keyCount < (buffSize - 1);
        // Only allow keys in range [32..125]
        if (bufferNotFull && key >= 32) {
            text[keyCount] = key;
            keyCount++;
            text[keyCount] = '\0';
        } else if (buffSize > 0 && IsKeyPressed(KEY_BACKSPACE)) {
            keyCount--;
            text[keyCount] = '\0';
        }
    }
    DrawText(text, x, y, FONT_SIZE, BLACK);
    return IsKeyPressed(KEY_ENTER);
}

static char consoleInputEntry[CMD_BUFFER_SIZE] = "";

void LuaGetTableField(lua_State *L, const char *tableName, const char *func) {
    lua_getglobal(L, tableName);
    int tableIndex = lua_gettop(L);
    lua_getfield(L, tableIndex, func);
}

void LuaWrite(lua_State *L, const char *str) {
    LuaGetTableField(L, "console", "write");
    lua_pushstring(L, str);
    if (lua_pcall(L, 1, 0, 0) != 0)
        printf("There was an error talking with the log module, %s\n", lua_tostring(L, -1));
    lua_pop(L, -1);
}

void LuaLog(lua_State *L, const char *str) {
    LuaGetTableField(L, "console", "log");
    lua_pushstring(L, str);
    if (lua_pcall(L, 1, 0, 0) != 0)
        printf("There was an error talking with the log module, %s\n", lua_tostring(L, -1));
    lua_pop(L, -1);
}

const char *LuaGetConsoleBuffer(lua_State *L) {
    LuaGetTableField(L, "console", "screen_buffer");
    const char *str = lua_tostring(L, -1);
    lua_pop(L, -1);
    return str;
}

int main() {

    int screenWidth = 690;
    int screenHeight = 560;

    InitWindow(screenWidth, screenHeight, "TDOR Lua test");
    SetExitKey(0);
    SetTargetFPS(60);

    // Initializes lua

    lua_State *L = luaL_newstate();
    luaL_openlibs(L); // We probably should not open sensitive libraries such as os


//    int error = luaL_dostring(L, "serpent = require('serpent')");

    int error = luaL_dofile(L, "data/core/lualib/init.lua");
    if (error == LUA_OK) {
        printf("Smooth!\n");
    } else {
        printf("Error loading file!\n");
    }

    bool consoleToggle = true;

    //--------------------------------------------------------------------------------------

    bool wantsToClose = false;

    // Main game loop
    while (!wantsToClose)    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        wantsToClose = WindowShouldClose();

        if (IsKeyPressed(KEY_GRAVE)) {
            consoleToggle = !consoleToggle;
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(WHITE);


        if (consoleToggle) {

            DrawText(">", 0, 0, FONT_SIZE, BLACK);
            if (SInputLine(FONT_SIZE, 0, consoleInputEntry, 255, true)) {
                LuaWrite(L, "]");
                LuaLog(L, consoleInputEntry);

                int r = luaL_dostring(L, consoleInputEntry);
                if (r == LUA_OK) {

                } else {
                    LuaLog(L, lua_tostring(L, -1));
                }


                consoleInputEntry[0] = '\0';
            }
            const char *screenBuf = LuaGetConsoleBuffer(L);
            DrawText(screenBuf, 0, FONT_SIZE, FONT_SIZE, BLACK);

            char result[32];
            sprintf(result, "%d", lua_gettop(L));
            DrawText(result, screenWidth - 2 * FONT_SIZE, screenHeight - FONT_SIZE, FONT_SIZE, BLACK);

            DrawText("Lua stack: ", 0, screenHeight - FONT_SIZE, FONT_SIZE, BLACK);

        }


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    lua_close(L);
    return 0;
}