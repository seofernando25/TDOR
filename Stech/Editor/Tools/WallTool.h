//
// Created by fer on 10/5/2021.
//

#ifndef TDOR_WALLTOOL_H
#define TDOR_WALLTOOL_H


#include "EditorTool.h"

class WallTool: public EditorTool{
public:
    void Update() override;

    void DrawUI() override;

    void AfterDrawCanvas() override;

    void PreDrawCanvas() override;
};


#endif //TDOR_WALLTOOL_H
