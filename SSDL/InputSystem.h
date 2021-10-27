//
// Created by fer on 10/12/2021.
//

#ifndef TDOR_INPUTSYSTEM_H
#define TDOR_INPUTSYSTEM_H

#include <SDL2/SDL.h>

class InputSystem {
public:
    static bool IsKeyDown(SDL_Keycode keycode);
    static bool IsKeyPressed(SDL_Keycode keycode);
    static bool IsKeyReleased(SDL_Keycode keycode);
    static bool IsMouseButtonPressed(SDL_Keycode which);

private:
    static const unsigned int *kbState;
    static const unsigned int *kbPrevState;
    int joystickCount = 0;
};


#endif //TDOR_INPUTSYSTEM_H
