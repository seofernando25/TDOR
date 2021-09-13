

#ifndef C_WALL_H
#define C_WALL_H

#include "c_line.h"

typedef struct Wall
{
    Line line;
    int wallDataIndex;
} Wall;

#endif
