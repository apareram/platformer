#include "Level.h"
#include "ResourceManager.h" // gestor de assets

Level::Level(Renderer* renderer, int levelId) {
    // se obtienen los recursos necesarios
    SDL_Renderer* rawRen = renderer->getRenderer();
    auto& res = ResourceManager::getInstance();

    background = res.loadTexture("assets/fondo.png", rawRen);
    platBigTex = res.loadTexture("assets/plataformaGrande.png", rawRen);
    platSmallTex = res.loadTexture("assets/platafomaPequena.png", rawRen);
    portalTex = res.loadTexture("assets/portal.png", rawRen);

    switch (levelId) {
    case 1:
        platforms.push_back({55, 65, 250, 100});
        platforms.push_back({400, 310, 100, 80});
        platforms.push_back({600, 200, 100, 80});
        platforms.push_back({850, 350, 250, 100});
        platforms.push_back({1200, 310, 100, 80});
        portal = {1250, 230, 50, 80};
        break;

    case 2:
        platforms.push_back({55, 65, 250, 100});
        platforms.push_back({350, 250, 100, 80});
        platforms.push_back({550, 150, 100, 80});
        platforms.push_back({800, 300, 250, 100});
        platforms.push_back({1100, 200, 100, 80});
        platforms.push_back({1400, 350, 250, 100});
        portal = {1500, 270, 50, 80};
        break;

    case 3:
        platforms.push_back({55, 65, 250, 100});
        platforms.push_back({300, 350, 100, 80});
        platforms.push_back({500, 250, 100, 80});
        platforms.push_back({700, 150, 100, 80});
        platforms.push_back({950, 300, 250, 100});
        platforms.push_back({1250, 200, 100, 80});
        platforms.push_back({1500, 100, 100, 80});
        platforms.push_back({1750, 350, 250, 100});
        portal = {1850, 270, 50, 80};
        break;

    default:
        portal = {200, 440, 50, 80};
        break;
    }
}

void Level::render(Renderer* renderer, float cameraX) {
    // se dibuja el fondo con parallax (se mueve mas lento que la camara)
    if (background) {
        renderer->drawTexture(background, -(cameraX * 0.5f), 0, 800, 600, false);
    }

    // se dibujan TODAS las plataformas con offset de camara
    for (const auto& p : platforms) {
        float screenX = p.x - cameraX;
        // plataformas anchas (>=200) usan textura grande, las demas la pequena
        if (p.w >= 200 && platBigTex) {
            renderer->drawTexture(platBigTex, screenX, p.y - 25, p.w, 120, false);
        } else if (platSmallTex) {
            renderer->drawTexture(platSmallTex, screenX, p.y - 30, p.w, 100, false);
        }
    }

    // se dibuja el portal
    if (portalTex) {
        float portalScreenX = portal.x - cameraX;
        renderer->drawTexture(portalTex, portalScreenX, portal.y, portal.w, portal.h, false);
    }
}