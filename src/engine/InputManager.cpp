#include "InputManager.h"

InputManager::InputManager() {}

InputManager::~InputManager() {}

bool InputManager::processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;  // Termina el bucle si se cierra la ventana
        }
    }
    return true;
}

bool InputManager::isKeyPressed(SDL_Keycode key) {
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    return keystates[SDL_GetScancodeFromKey(key)];
}