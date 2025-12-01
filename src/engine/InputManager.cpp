#include "InputManager.h"

InputManager::InputManager() {}

InputManager::~InputManager() {}

bool InputManager::processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) { // mientras existan eventos
        if (event.type == SDL_EVENT_QUIT) { // si el usuario presiona la X pa cerrar el juego
            return false; // running se vuelve falso
        }
    }
    return true;
}

// inspecror
bool InputManager::isKeyPressed(SDL_Keycode key) { // toma una "foto" del teclado
    const bool* keystates = SDL_GetKeyboardState(NULL); // creamos un arreglo con el estado de todas las teclas
    SDL_Scancode scancode = SDL_GetScancodeFromKey(key, nullptr); // captura el estado de la tecla de interes
    
    if (scancode != SDL_SCANCODE_UNKNOWN) {
        return keystates[scancode]; // regresa el estado de la tecla de interes
    }
    return false;
}