//
// Created by fer on 10/5/2021.
//

#include <StechEditor.h>
#include "WallTool.h"

void WallTool::Update() {
    // Find the node we are hovering
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



    if (selectedVertex != -1){
        if (IsMouseButtonUp(0) && hoveringSomething){
            // Add walls
            Vector2 line = {(float)selectedVertex,(float)hoveredIndex};
            StechEditor::instance->levelGeometry.lines.push_back(line);
            selectedVertex = -1;
        }
    }

    // Unselect vertex if released
    if (IsMouseButtonUp(0)){
        selectedVertex = -1;
    }
}

void WallTool::DrawUI() {
    EditorTool::DrawUI();
}

void WallTool::AfterDrawCanvas() {
    EditorTool::AfterDrawCanvas();
}

void WallTool::PreDrawCanvas() {
    if (selectedVertex != -1){
        Vector2 vert = StechEditor::instance->levelGeometry.vertex[selectedVertex];
        vert.y *= -1;
        Vector2 end = StechEditor::instance->worldMousePosition;
        end.y *= -1;
        DrawLineEx(vert, end, 5, WHITE);
    }
    EditorTool::PreDrawCanvas();
}
