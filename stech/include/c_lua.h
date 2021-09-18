#pragma once

#include <raylib.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


void StackDump(lua_State *L);

void DoString(lua_State *L, const char *str);

void QuickPushVariable(lua_State *L, const char *variable);

bool PushField(lua_State *L, const char *field);

void ConsoleWrite(lua_State *L, const char *str);

void ConsoleLog(lua_State *L, const char *str);

const char *GetConsoleBuffer(lua_State *L);

Vector2 GetVector2(lua_State *L, int position);

Vector3 GetVector3(lua_State *L, int position);

Vector4 GetVector4(lua_State *L, int position);

Rectangle GetRect(lua_State *L, int position);

int luaDrawRect(lua_State *L);

int luaDrawText(lua_State *L);