//
// Created by fer on 10/5/2021.
//


#include "VertexTool.h"
#include <raylib.h>
#include <Math/CollisionChecks.h>
#include <iomanip>
#include <sstream>
#include "StechEditor.h"

void VertexTool::Update() {
    int hoveredIndex = -1;
    bool hoveringSomething = false;
    for (auto &vert : StechEditor::instance->levelGeometry.vertex){
        hoveredIndex++;
        if (collision_circle_point(vert, StechEditor::instance->worldMousePosition, 10)){
            hoveringSomething = true;
            break;
        }
    }

    // Selected vertex stuff
    if (hoveringSomething && IsMouseButtonPressed(0) && selectedVertex == -1){
        selectedVertex = hoveredIndex;
    }

    if (IsMouseButtonUp(0)){
        selectedVertex = -1;
    }

    if (selectedVertex != -1){
        if (IsMouseButtonDown(0)){
            // Move it to cursor
            StechEditor::instance->levelGeometry.vertex[selectedVertex] = StechEditor::instance->worldMousePosition;
        }
    } else{
        // Create new vertex
        if (IsMouseButtonPressed(0) && !hoveringSomething){
            StechEditor::instance->levelGeometry.vertex.push_back(StechEditor::instance->worldMousePosition);
            selectedVertex = StechEditor::instance->levelGeometry.vertex.size() - 1;
        }

        // Delete vertex
        if (IsMouseButtonDown(1) && hoveringSomething){
            StechEditor::instance->levelGeometry.RemoveVertex(hoveredIndex);
            selectedVertex = -1;
        }
    }

    DrawText(std::to_string(hoveredIndex).c_str(), 0, 50, 12, WHITE);
}

void VertexTool::DrawUI() {

}

void VertexTool::AfterDrawCanvas() {
}

void VertexTool::PreDrawCanvas() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2);
    for (auto &vert : StechEditor::instance->levelGeometry.vertex){

        ss << "(" << vert.x << ", " << vert.y << ")";
        DrawText(ss.str().c_str(), vert.x + 10, -vert.y + 10, 10, WHITE);
        ss.str("");
    }
}


