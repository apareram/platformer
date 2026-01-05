#include "Level.h"
#include "ResourceManager.h" // gestor de assets

Level::Level(Renderer* renderer, int levelId) {
    // se obtienen los recursos necesarios
    SDL_Renderer* rawRen = renderer->getRenderer();
    auto& res = ResourceManager::getInstance();

    background = res.loadTexture("assets/fondo.png", rawRen);
    platBigTex = res.loadTexture("assets/plataformaGrande.png", rawRen);
    platSmallTex = res.loadTexture("assets/platafomaPequena.png", rawRen);

    switch (levelId)
    {
    case 1:
        platforms.push_back({55, 65, 250, 100});
        platforms.push_back({400, 310, 100, 80});
        platforms.push_back({600, 200, 100, 80}); 
        platforms.push_back({850, 350, 250, 100}); 
        platforms.push_back({1200, 310, 100, 80});
        break;
    
    case 2:
        platforms.push_back({55, 65, 250, 100});
        break;
    }
}

void Level::render(Renderer* renderer, float cameraX) {
    // se dibuja el fondo (Siempre primero)
    // si se divide cameraX / 2, el fondo se mueve más lento dando sensación de profundidad.
    if (background) {
        renderer->drawTexture(background, -(cameraX * 0.5f), 0, 800, 600, false);
        // Nota: se necesitara dibujar una segunda copia del fondo al lado para que no se acabe la imagen,
    }

    

    for (const auto& p : platforms){
        float screenX = p.x - cameraX; // Coordenada de pantalla = Mundo - Cámara
        // Dibujamos usando screenX
    }
    // se dibujan las plataformas (-10 en Y para que quede al tiro)
    if (platforms.size() > 0 && platBigTex) {  // se dibuja la primera plataforma (grande)
        renderer->drawTexture(platBigTex, platforms[0].x, platforms[0].y - 25, platforms[0].w, 120, false);
    } else if (platforms.size() > 1 && platSmallTex){ // se dibuja la segunda plataforma (Pequeña)
        renderer->drawTexture(platSmallTex, platforms[1].x, platforms[1].y -30, platforms[1].w, 100, false);
    }

    // NOTA PARA EL FUTURO:
    // Si tuvieras 100 plataformas, no harías if(size > 0), if(size > 1)...
    // Crearías una clase "Tile" o "PlatformObject" que guarde su propia textura.
    // Pero para este nivel de 2 plataformas, esto es perfecto y eficiente.
}