#pragma once

#include "raylib.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Settings
{
    unsigned short version;
    int screenWidth;
    int screenHeight;
    bool screenFullscreen;
    bool showFps;

} Settings;

bool LoadSettings(Settings *settings);
bool SaveSettings(Settings *settings);
Settings GetDefaultSettings(void);
