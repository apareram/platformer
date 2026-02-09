#pragma once
#include <vector>
#include "Physics.h" // struct Platform
#include "Renderer.h"

class Level {
public:
    Level(Renderer* renderer, int levelId);

    // xOffset (la posición de la cámara)
    void render(Renderer* renderer, float cameraX);

    const std::vector<Platform>& getPlatforms() const { return platforms; }
    const Portal& getPortal() const { return portal; }

    static const int TOTAL_LEVELS = 3;

private:
    std::vector<Platform> platforms;
    Portal portal;
    SDL_Texture* background;
    SDL_Texture* platBigTex;
    SDL_Texture* platSmallTex;
    SDL_Texture* portalTex;
};