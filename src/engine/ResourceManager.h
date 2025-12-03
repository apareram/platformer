#pragma once
#include <map>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class ResourceManager {
public:
    static ResourceManager& getInstance() { // singleton
        static ResourceManager instance;
        return instance;
    }

    // carga o devuelve una textura ya cargada
    SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);
    
    // limpieza
    void clear();

private:
    ResourceManager() {} // constructor privado
    std::map<std::string, SDL_Texture*> textures;
};