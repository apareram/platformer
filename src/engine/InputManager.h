#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

// SDL3 CHANGE: Update include
#include <SDL3/SDL.h>

class InputManager {
public:
    InputManager();
    ~InputManager();
    bool processInput();
    bool isKeyPressed(SDL_Keycode key);
};

#endif