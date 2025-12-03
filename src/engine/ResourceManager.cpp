#include "ResourceManager.h"
#include <iostream>

SDL_Texture* ResourceManager::loadTexture(const std::string& path, SDL_Renderer* renderer) {
    // si la imagen ya se cargo, devuelve la existente
    if (textures.find(path) != textures.end()) {
        return textures[path]; 
    }

    // si no, la carga ahora
    SDL_Texture* newTex = IMG_LoadTexture(renderer, path.c_str());
    if (!newTex) {
        SDL_Log("Error cargando textura: %s", path.c_str());
        return nullptr;
    }

    // la guarda en el mapa
    textures[path] = newTex;
    return newTex;
}

void ResourceManager::clear() {
    for (auto& pair : textures) {
        SDL_DestroyTexture(pair.second);
    }
    textures.clear();
}