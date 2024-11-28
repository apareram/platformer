#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL2/SDL.h>

class InputManager {
public:
    InputManager();                    // Constructor
    ~InputManager();                   // Destructor
    bool processInput();               // Procesa los eventos de entrada
    bool isKeyPressed(SDL_Keycode key); // Verifica si una tecla específica está presionada
};

#endif