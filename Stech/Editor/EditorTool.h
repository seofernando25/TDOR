//
// Created by fer on 10/5/2021.
//

#ifndef TDOR_EDITORTOOL_H
#define TDOR_EDITORTOOL_H

// Base class for each editor tool loop
class EditorTool {
public:
    virtual void Update() {};
    virtual void DrawUI() {};
    virtual void AfterDrawCanvas() {};
    virtual void PreDrawCanvas() {};
};


#endif //TDOR_EDITORTOOL_H
