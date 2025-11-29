// main.cpp
#include <iostream>
#include <stdexcept>
#include <SDL3/SDL.h>
#include "engine/Core.h"

int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        std::cerr << "SDL init error: " << SDL_GetError() << "\n";
        return -1;
    }

    try {
        Core core;
        core.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    SDL_Quit();
    return 0;
}