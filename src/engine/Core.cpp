#include "Core.h"
#include <stdexcept>
#include <iostream>

// constructor
Core::Core() : running(true){ // funcion core pertenece a la clase core y running empieza true
    renderer = std::make_unique<Renderer>(800, 600, "Platformer");
    inputManager = std::make_unique<InputManager>();
    physics = std::make_unique<Physics>(1200.0f, 520.0f);

    // se crea al jugador y al nivel, se les pasa el renderer para que carguen sus cosas
    player = std::make_unique<Player>(renderer.get());
    level = std::make_unique<Level>(renderer.get());

    menu = std::make_unique<Menu>(renderer.get());
    currentState = MENU;
}

// destructor
Core::~Core() {}

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
            // el menú solo escucha si presionamos Enter
            if (menu->handleInput(inputManager.get())) {
                currentState = PLAYING; 
                std::cout << "Iniciando Juego..." << std::endl;
            }
            break;

        case PLAYING:
            //se sigue la lógica normal del juego solo corre si estamos en PLAYING
            player->handleInput(inputManager.get());
            physics->update(player->getBody(), dt, level->getPlatforms());
            player->update(dt);
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
            level->render(renderer.get());
            player->render(renderer.get());
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