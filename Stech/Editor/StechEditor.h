//
// Created by fer on 10/5/2021.
//

#ifndef STECHEDITOR_H
#define STECHEDITOR_H


#include <Scene/LevelGeometry.h>
#include "EditorTool.h"
#include <raylib.h>
#include <string>
#include <Math/CollisionChecks.h>
#include <Tools/VertexTool.h>
#include <Tools/WallTool.h>

class StechEditor {
public:
    static StechEditor* instance;
    StechEditor(int window_w, int window_h);
    void Update();
    void DrawUI();
    void DrawCanvas();
    void Run();

    virtual ~StechEditor();

    EditorTool* currentTool;
    VertexTool* veditor;
    WallTool* weditor;

    LevelGeometry levelGeometry;
    Vector2 worldMousePosition{};
    int toolSelected = 0;
    Camera2D camera2d{0};
    float camera3dRotation = 0;
    Camera3D camera3d{0};
    // TODO Swap 3d and 2d with preview or swapping
};


#endif //STECHEDITOR_H
