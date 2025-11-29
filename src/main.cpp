// main.cpp
#include <iostream>
#include <stdexcept>
#include <SDL2/SDL.h>
#include "engine/Core.h"

struct SDLGuard {
    SDLGuard() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            throw std::runtime_error(std::string("SDL_Init failed: ") + SDL_GetError());
        }
    }
    ~SDLGuard() noexcept {
        SDL_Quit();
    }
    // non-copyable
    SDLGuard(const SDLGuard&) = delete;
    SDLGuard& operator=(const SDLGuard&) = delete;
};

int main() {
    try {
        SDLGuard sdl;            // initializes SDL, will call SDL_Quit() in destructor
        Core core;               // may throw
        core.run();              // main game loop
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
        return -1;
    } catch (...) {
        std::cerr << "Unhandled unknown exception\n";
        return -1;
    }
}