#include <Core/Application.h>
#include <Entities/EBillboard.h>
#include <Entities/EPawn.h>
#include <Entities/EReferenceGrid.h>

#include "raylib.h"

#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480

int main() {
    Application editor("Seditor");
    Scene myLevel;
    Texture tex = LoadTexture("data/retro_gato.png");
    EReferenceGrid refGrid;
    EBillboard gato_entity(tex);
    EPawn pawn;
    pawn.position = {0, 1, 2};


    myLevel.entities.push_back(&gato_entity);
    myLevel.entities.push_back(&refGrid);
    myLevel.entities.push_back(&pawn);
    myLevel.cameras.push_back(&pawn);
    editor.scenes.push_back(&myLevel);

    editor.Run();
    return 0;
}