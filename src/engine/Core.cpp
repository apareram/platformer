#include "Core.h"
#include <stdexcept>
#include <iostream>

// constructor
Core::Core() : running(true), currentLevel(1) {
    renderer = std::make_unique<Renderer>(800, 600, "Platformer");
    inputManager = std::make_unique<InputManager>();
    physics = std::make_unique<Physics>(1200.0f, 520.0f);

    player = std::make_unique<Player>(renderer.get());
    level = std::make_unique<Level>(renderer.get(), currentLevel);

    menu = std::make_unique<Menu>(renderer.get());
    currentState = MENU;

    camera = {0, 0, 800, 600};
}

// destructor
Core::~Core() {}

void Core::loadLevel(int levelId) {
    currentLevel = levelId;
    level = std::make_unique<Level>(renderer.get(), currentLevel);

    // resetear jugador al inicio del nivel
    Body& body = player->getBody();
    body.x = 100;
    body.y = 100;
    body.vx = 0;
    body.vy = 0;
    body.grounded = false;
    body.jumpCount = 0;
    body.angularVel = 0;
    body.angle = 0;

    camera.x = 0;
}

void Core::run() {
    Uint64 last = SDL_GetPerformanceCounter();
    
    while (running) {
        Uint64 now = SDL_GetPerformanceCounter();
        float dt = (now - last) / (float)SDL_GetPerformanceFrequency();
        last = now;

        running = inputManager->processInput();

        update(dt);
        render();
    }
}

void Core::update(float dt) {
    switch (currentState) {
        case MENU:
            if (menu->handleInput(inputManager.get())) {
                currentState = PLAYING;
                loadLevel(1);
                std::cout << "Iniciando Juego..." << std::endl;
            }
            break;

        case PLAYING:
            player->handleInput(inputManager.get());
            physics->update(player->getBody(), dt, level->getPlatforms());
            player->update(dt);

            // camara sigue al jugador
            camera.x = player->getBody().x - 400;
            if (camera.x < 0) camera.x = 0;

            // colision con portal -> siguiente nivel
            if (physics->checkPortalCollision(player->getBody(), level->getPortal())) {
                if (currentLevel < Level::TOTAL_LEVELS) {
                    loadLevel(currentLevel + 1);
                    std::cout << "Nivel " << currentLevel << " iniciado!" << std::endl;
                } else {
                    currentState = MENU;
                    std::cout << "Juego completado!" << std::endl;
                }
            }
            break;
    }
}

void Core::render() {
    renderer->clear();

    switch (currentState) {
        case MENU:
            // level->render(renderer.get()); // si queremos que se vea el fondo de algun nivel
            menu->render(renderer.get());
            break;

        case PLAYING:
            level->render(renderer.get(), camera.x);
            player->render(renderer.get(), camera.x);
            // Debug...
            break;
    }

    renderer->present();
}
/*
// --- MODO DEBUG: DIBUJAR LAS CAJAS INVISIBLES ---
    // jugador
    SDL_SetRenderDrawColor(renderer->getRenderer(), 0, 255, 0, 255); // Verde
    SDL_FRect playerRect = {player.x, player.y, player.width, player.height};
    SDL_RenderRect(renderer->getRenderer(), &playerRect); // Dibuja solo el borde
    // plataformas
    SDL_SetRenderDrawColor(renderer->getRenderer(), 255, 0, 0, 255); // Rojo
    for(const auto& p : platforms) {
        SDL_FRect platformRect = {p.x, p.y, p.w, p.h};
        SDL_RenderRect(renderer->getRenderer(), &platformRect);
    }
    // Restaurar color negro por seguridad
    SDL_SetRenderDrawColor(renderer->getRenderer(), 0, 0, 0, 255);
    // --------------------------------------------------------------
 */