//
// Created by fer on 9/30/2021.
//

#ifndef GAMESCRIPT_H
#define GAMESCRIPT_H

#include <string>

class GameScript {
public:
    std::string fileName;
    bool loaded = false;
    bool enabled = true;

    // virtual void Awake() {};
    // TODO OTher script thing likes update etc
};


#endif //GAMESCRIPT_H
