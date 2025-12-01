// main.cpp
#include <iostream>
#include <stdexcept>
#include <SDL3/SDL.h>
#include "engine/Core.h"

int main() {
    // se inicia SDL con una condición para evitar errores
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        std::cerr << "SDL init error: " << SDL_GetError() << "\n";
        return -1;
    }

    // se crea una instacioa de la clase core
    try {
        Core core;
        core.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    // se cierra SDL siguiendo buenas practicas
    SDL_Quit();
    return 0;
}