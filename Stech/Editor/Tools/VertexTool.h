//
// Created by fer on 10/5/2021.
//

#ifndef TDOR_VERTEXTOOL_H
#define TDOR_VERTEXTOOL_H


#include "EditorTool.h"


class VertexTool: public EditorTool {
public:
    int selectedVertex = -1;
    void Update() override;
    void DrawUI() override;
    void AfterDrawCanvas() override;
    void PreDrawCanvas() override;
};


#endif //TDOR_VERTEXTOOL_H
