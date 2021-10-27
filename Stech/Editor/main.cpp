#include <Core/Application.h>
#include <SUI/SPanel.h>
#include "StechEditor.h"
#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480


int main() {
    StechEditor editor(1280, 720);
    editor.Run();
    return 0;
}