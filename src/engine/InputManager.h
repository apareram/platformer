#ifndef INPUTMANAGER_H //evitan que el compilador copie y pegue este archivo dos veces por error
#define INPUTMANAGER_H
#include <SDL3/SDL.h>

class InputManager {
public:
    InputManager();
    ~InputManager();
    bool processInput();
    bool isKeyPressed(SDL_Keycode key);
};

#endif