#include "InputManager.h"

InputManager::InputManager() {}

InputManager::~InputManager() {}

bool InputManager::processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // SDL3 CHANGE: SDL_QUIT is now SDL_EVENT_QUIT
        if (event.type == SDL_EVENT_QUIT) {
            return false;
        }
    }
    return true;
}

bool InputManager::isKeyPressed(SDL_Keycode key) {
    // SDL3 CHANGE: Returns a 'bool' array, not 'Uint8'
    // SDL3 CHANGE: We don't need to pass a size variable if we don't want it, so just NULL is fine.
    const bool* keystates = SDL_GetKeyboardState(NULL);
    
    // SDL3 CHANGE: SDL_GetScancodeFromKey requires a second argument (modstate). 
    // We pass nullptr because we just want the base scancode.
    SDL_Scancode scancode = SDL_GetScancodeFromKey(key, nullptr);
    
    if (scancode != SDL_SCANCODE_UNKNOWN) {
        return keystates[scancode];
    }
    return false;
}