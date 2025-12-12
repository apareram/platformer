#include "Level.h"
#include "ResourceManager.h" // gestor de assets

Level::Level(Renderer* renderer, int levelId) {
    // se obtienen los recursos necesarios
    SDL_Renderer* rawRen = renderer->getRenderer();
    auto& res = ResourceManager::getInstance();

    switch (levelId)
    {
    case 1:
        // se cargan las texturas
        background = res.loadTexture("assets/fondo.png", rawRen);
        platBigTex = res.loadTexture("assets/plataformaGrande.png", rawRen);
        platSmallTex = res.loadTexture("assets/platafomaPequena.png", rawRen);
        // plataforma Grande (X: 55, Y: 65)
        Platform p1 = {55, 65, 250, 100};
        platforms.push_back(p1);

        // plataforma Pequeña (X: 400, Y: 310)
        Platform p2 = {400, 310, 100, 80};
        platforms.push_back(p2);
        break;
    
    case 2:
        // se cargan las texturas
        background = res.loadTexture("assets/fondo.png", rawRen);
        platBigTex = res.loadTexture("assets/plataformaGrande.png", rawRen);
        platSmallTex = res.loadTexture("assets/platafomaPequena.png", rawRen);
        // plataforma Grande (X: 55, Y: 65)
        Platform p1 = {55, 65, 250, 100};
        platforms.push_back(p1);

        // plataforma Pequeña (X: 400, Y: 310)
        Platform p2 = {400, 310, 100, 80};
        platforms.push_back(p2);
        break;
    }
}

void Level::render(Renderer* renderer) {
    // se dibuja el fondo (Siempre primero)
    if (background) {
        renderer->drawTexture(background, 0, 0, 800, 600, false);
    }

    // se dibujan las plataformas (-10 en Y para que quede al tiro)

    // se dibuja la primera plataforma
    if (platforms.size() > 0 && platBigTex) {
        // La física dice Y=65, dibujamos en Y=55 (65 - 10)
        // La altura visual es 120 (más alta que la física para las raíces colgando)
        renderer->drawTexture(platBigTex, platforms[0].x, platforms[0].y - 20, platforms[0].w, 120, false);
    }

    // se dibuja la segunda plataforma (Pequeña)
    if (platforms.size() > 1 && platSmallTex) {
        // La física dice Y=310, dibujamos en Y=300 (310 - 10)
        renderer->drawTexture(platSmallTex, platforms[1].x, platforms[1].y - 20, platforms[1].w, 100, false);
    }

    // NOTA PARA EL FUTURO:
    // Si tuvieras 100 plataformas, no harías if(size > 0), if(size > 1)...
    // Crearías una clase "Tile" o "PlatformObject" que guarde su propia textura.
    // Pero para este nivel de 2 plataformas, esto es perfecto y eficiente.
}