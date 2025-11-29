#include "Renderer.h"
#include <iostream>

Renderer::Renderer(int width, int height, const std::string& title) {
    // SDL3 CHANGE: No x, y arguments. No SDL_WINDOW_SHOWN flag needed.
    window = SDL_CreateWindow(title.c_str(), width, height, 0);
    if (!window) {
        throw std::runtime_error(std::string("Error creating window: ") + SDL_GetError());
    }

    // SDL3 CHANGE: No index (-1) or flags. Second arg is the driver name (NULL for default).
    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        throw std::runtime_error(std::string("Error creating renderer: ") + SDL_GetError());
    }
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Renderer::clear() {
    // SDL3 CHANGE: SetRenderDrawColor returns bool, but void is fine for basic usage
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
    SDL_RenderClear(renderer);
}

void Renderer::present() {
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Renderer::getRenderer() {
    return renderer;
}