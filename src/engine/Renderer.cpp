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

// función para cargar las texturas
SDL_Texture* Renderer::loadTexture(const std::string& path) {
    SDL_Texture* tex = IMG_LoadTexture(renderer, path.c_str());
    if (!tex) {
        SDL_Log("No se pudo cargar la imagen %s: %s", path.c_str(), SDL_GetError());
    }
    return tex;
}

// funcion para imprimir las texturas
void Renderer::drawTexture(SDL_Texture* texture, float x, float y, float w, float h, bool flipX) {
    if (!texture) return; // Si no hay imagen, no hagas nada

    SDL_FRect dstRect = { x, y, w, h };
    
    // SDL_FLIP_HORIZONTAL es para mirar a la izquierda
    // SDL_FLIP_NONE es normal
    SDL_FlipMode flip = flipX ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    SDL_RenderTextureRotated(renderer, texture, NULL, &dstRect, 0.0, NULL, flip);
}