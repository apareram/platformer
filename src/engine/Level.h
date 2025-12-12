#pragma once
#include <vector>
#include "Physics.h" // struct Platform
#include "Renderer.h"

class Level {
public:
    Level(Renderer* renderer);
    void render(Renderer* renderer, int levelId);
    
    // para que la física sepa contra qué chocar
    const std::vector<Platform>& getPlatforms() const { return platforms; }

private:
    std::vector<Platform> platforms;
    SDL_Texture* background;
    SDL_Texture* platBigTex;
    SDL_Texture* platSmallTex;
};