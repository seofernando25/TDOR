#include "c_lua.h"

#define LuaToInt(L, i) (int)lua_tonumber(L, i)
#define LuaToFloat(L, i) (float)lua_tonumber(L, i)
#define LuaToUChar(L, i) (unsigned char)lua_tonumber(L, i)


void StackDump(lua_State *L) {
    int i;
    int top = lua_gettop(L);
    for (i = 1; i <= top; i++) { /* repeat for each level */
        int t = lua_type(L, i);
        switch (t) {

        case LUA_TSTRING: /* strings */
            printf("`%s'", lua_tostring(L, i));
            break;

        case LUA_TBOOLEAN: /* booleans */
            printf(lua_toboolean(L, i) ? "true" : "false");
            break;

        case LUA_TNUMBER: /* numbers */
            printf("%g", LuaToFloat(L, i));
            break;

        default: /* other values */
            printf("%s", lua_typename(L, t));
            break;
        }
        printf("  "); /* put a separator */
    }
    printf("\n"); /* end the listing */
}

void DoString(lua_State *L, const char *str)
{
    int r = luaL_dostring(L, str);
    if (r != LUA_OK)
    {
        const char *error = lua_tostring(L, -1);
        printf("%s\n", error);
        lua_pop(L, 1);
        ConsoleLog(L, error);
    }
}

bool PushField(lua_State *L, const char *field)
{
    if (!lua_istable(L, -1))
    {
        printf("top is not lua table!\n");
        return false;
    }
    lua_getfield(L, -1, field);
    return true;
}

void QuickPushVariable(lua_State *L, const char *variable) {
    char buffer[128] = "_internal_temp=";
    snprintf(buffer + strlen(buffer), 128 - strlen(buffer), "%s", variable);
    DoString(L, buffer);
    lua_getglobal(L, "_internal_temp");
}

void ConsoleWrite(lua_State *L, const char *str)
{
    QuickPushVariable(L, "console.write");
    lua_pushstring(L, str);
    if (lua_pcall(L, 1, 0, 0) != 0)
        printf("There was an error talking with the log module, %s\n", lua_tostring(L, -1));
}

void ConsoleLog(lua_State *L, const char *str)
{
    QuickPushVariable(L, "console.log");
    lua_pushstring(L, str);
    if (lua_pcall(L, 1, 0, 0) != 0)
        printf("There was an error talking with the log module, %s\n", lua_tostring(L, -1));
}

const char *GetConsoleBuffer(lua_State *L)
{
    lua_getglobal(L, "console");
    lua_getfield(L, -1, "screen_buffer");
    const char *str = lua_tostring(L, -1);
    lua_pop(L, 2);
    return str;
}

Vector2 GetVector2(lua_State *L, int position)
{
    lua_getfield(L, position, "x");
    lua_getfield(L, position, "y");
    Vector2 vec = {LuaToFloat(L, -2), LuaToFloat(L, -1)};
    lua_pop(L, 2);
    return vec;
}

Vector3 GetVector3(lua_State *L, int position)
{
    lua_getfield(L, position, "x");
    lua_getfield(L, position, "y");
    lua_getfield(L, position, "z");
    Vector3 vec = {LuaToFloat(L, -3), LuaToFloat(L, -2), LuaToFloat(L, -1)};
    lua_pop(L, 3);
    return vec;
}

Vector4 GetVector4(lua_State *L, int position)
{
    lua_getfield(L, position, "x");
    lua_getfield(L, position, "y");
    lua_getfield(L, position, "z");
    lua_getfield(L, position, "w");
    Vector4 vec = {LuaToFloat(L, -4), LuaToFloat(L, -3), LuaToFloat(L, -2), LuaToFloat(L, -1)};
    lua_pop(L, 4);
    return vec;
}

Rectangle GetRect(lua_State *L, int position)
{
    lua_getfield(L, position, "x");
    lua_getfield(L, position, "y");
    lua_getfield(L, position, "w");
    lua_getfield(L, position, "h");
    Rectangle rect = {LuaToFloat(L, -4), LuaToFloat(L, -3), LuaToFloat(L, -2), LuaToFloat(L, -1)};
    lua_pop(L, 4);
    return rect;
}

int luaDrawRect(lua_State *L) {
    Rectangle rect{LuaToFloat(L, 1), LuaToFloat(L, 2), LuaToFloat(L, 3), LuaToFloat(L, 4)};
    Color col{LuaToUChar(L, 5), LuaToUChar(L, 6), LuaToUChar(L, 7), LuaToUChar(L, 8)};
    DrawRectangleRec(rect, col);
    return 1;
}

int luaDrawText(lua_State *L) {
    // Text - x - y - font size - color
    Color col{LuaToUChar(L, 5), LuaToUChar(L, 6), LuaToUChar(L, 7), LuaToUChar(L, 8)};
    DrawText(lua_tostring(L, 1), LuaToInt(L, 2), LuaToInt(L, 3), LuaToInt(L, 4), col);
    return 1;
}