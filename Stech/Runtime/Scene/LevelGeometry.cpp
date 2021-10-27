//
// Created by fer on 10/6/2021.
//

#include "LevelGeometry.h"

bool LevelGeometry::RemoveVertex(int vertexIndex) {
    if(vertexIndex < 0 || vertexIndex > vertex.size() -1)
        return false;

    // Delete the vertex
    vertex.erase(vertex.begin() + vertexIndex);

    auto line = lines.begin();
    while (line != lines.end()){
        // Delete all lines that use that vertex
        if ((int)line->x == vertexIndex || (int)line->y == vertexIndex)
            line = lines.erase(line);
        else
            line++;
    }

    line = lines.begin();
    while (line != lines.end()){
        // Shift that use that vertex down
        if((int)line->x > vertexIndex)
            line->x--;
        if((int)line->y > vertexIndex)
            line->y--;
        ++line;
    }

    return true;
}