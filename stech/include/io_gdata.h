#pragma once

#define RES_MAX_STR 32

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef struct GResource
{
    char name[RES_MAX_STR];
    unsigned int size;
    void *data;
} GResource;

typedef struct GData
{
    unsigned int size;
    GResource *resources;
} GData;

// Loads a GData from a file
// and resources inside it
bool LoadGDATA(GData *gdata, const char *filename);

// Write GData to file
bool SaveGDATA(GData *gdata, const char *filename);

// Free GData
// and all resources inside it
void FreeGDATA(GData *gdata);

// Write data to GData
void WriteToGDATA(GData *gdata, const char *resourceName, int resourceSize, char *resourceData);

GData *CreateGDATA(void);