//
// Created by fer on 10/5/2021.
//


#include "StechEditor.h"
#include "imgui.h"



StechEditor* StechEditor::instance = nullptr;

StechEditor::StechEditor(int window_w, int window_h) {
    instance = this;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(window_w, window_h, "StechEditor");
    SetWindowMinSize(window_w/4, window_h/4);
    SetExitKey(0);
    SetTargetFPS(60);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplRaylib_Init();
    ImGui::StyleColorsDark();

    camera2d.target = {0, 0};
    camera2d.zoom = 1.0f;
    camera2d.rotation = 0.0f;
    camera2d.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };

    camera3d.target = {0, 0, 1};
    camera3d.fovy = 75.f;
    camera3d.projection = CAMERA_PERSPECTIVE;
    camera3d.up = {0, 1, 0};

    veditor = new VertexTool();
    weditor = new WallTool();
    currentTool = veditor;
}

StechEditor::~StechEditor() {
    delete veditor;
    delete weditor;
}

void StechEditor::Run() {
    bool wantsToClose = false;
    float f = 0.f;




    // Main game loop
    while (!wantsToClose) // Detect window close button or ESC key
    {
        wantsToClose = WindowShouldClose();
        ImGui_ImplRaylib_NewFrame(); // Imgui window data update
        ImGui_ImplRaylib_ProcessEvent(); // Adds pressed key to io buffer
        Update();
        BeginDrawing();
        ClearBackground(BLACK);
        DrawCanvas();
        DrawUI();

        // Create a window called "My First Tool", with a menu bar.
        ImGui::Begin("Demo window");
        ImGui::Button("Hello!");
        ImGui::End();

        ImGui::Render();
        EndDrawing();
    }

    CloseWindow();
}

void StechEditor::Update() {
    camera3d.position = {camera2d.target.x, 3, camera2d.target.y};
    camera3d.target = {camera3d.position.x + cosf(camera3dRotation)*5, 3, camera3d.position.z + sinf(camera3dRotation)*5};

    camera2d.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    worldMousePosition = GetScreenToWorld2D(GetMousePosition(), camera2d);
    worldMousePosition.y *= -1;


    // Camera Zoom
    float mw = GetMouseWheelMove()*0.25;
    camera2d.zoom += mw;
    if (camera2d.zoom < 0.25)
        camera2d.zoom = 0.25;
    if(mw != 0.f ){
        float dx = worldMousePosition.x - camera2d.target.x;
        float dy = worldMousePosition.y - camera2d.target.y;

        worldMousePosition = GetScreenToWorld2D(GetMousePosition(), camera2d);
        worldMousePosition.y *= -1;

        float ndx = worldMousePosition.x - camera2d.target.x;
        float ndy = worldMousePosition.y - camera2d.target.y;

        camera2d.target.x += dx - ndx;
        camera2d.target.y -= dy - ndy;
    }

    currentTool->Update();

    // Swap Tools
    if (IsKeyDown(KEY_Z))
        currentTool = veditor;
    if (IsKeyDown(KEY_X))
        currentTool = weditor;

    // Move camera
    if(IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)){
        Vector2 mdelta =  GetMouseDelta();
        camera2d.target.x -= mdelta.x / camera2d.zoom;
        camera2d.target.y -= mdelta.y / camera2d.zoom;
    }

}



void StechEditor::DrawCanvas() {
    BeginMode2D(camera2d);
    currentTool->PreDrawCanvas();

    DrawCircle(0, 0, 5, GRAY);


    for (const auto &vert : levelGeometry.vertex){
        if(collision_circle_point(vert, worldMousePosition, 10))
            DrawCircle(vert.x, -vert.y, 10, GREEN);
        else
            DrawCircle((int)vert.x, (int)-vert.y, 10, WHITE);
        DrawCircle((int)vert.x, (int)-vert.y, 2, BLACK);
    }

    for (const auto &line : levelGeometry.lines){
        Vector2 p1 = levelGeometry.vertex[line.x];
        Vector2 p2 = levelGeometry.vertex[line.y];
        DrawLineEx({p1.x, -p1.y}, {p2.x, -p2.y}, 5, WHITE);
    }

    DrawCircle(camera3d.position.x, camera3d.position.z, 5.f, RED);
    DrawLineEx({camera3d.position.x, camera3d.position.z}, {camera3d.target.x , camera3d.target.z}, 2, LIGHTGRAY);

    currentTool->AfterDrawCanvas();
    EndMode2D();
}

void StechEditor::DrawUI() {
    std::string mouse_str = "Mouse: " + std::to_string(worldMousePosition.x) + " " + std::to_string(worldMousePosition.y);
    std::string cam_str = "Cam: (" + std::to_string(camera2d.target.x) + ", " + std::to_string(camera2d.target.y) + ") Z: " + std::to_string(camera2d.zoom);
    DrawText(mouse_str.c_str(), 0, 0, 24, WHITE);
    DrawText(cam_str.c_str(), 0, 24, 24, WHITE);
//    DrawCircle(GetScreenWidth()/2, GetScreenHeight()/2, 5.f, LIGHTGRAY);

    currentTool->DrawUI();
}

