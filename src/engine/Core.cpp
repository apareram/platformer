#include "Core.h"
#include <stdexcept>
#include <iostream>

// constructor
Core::Core() : running(true){ // funcion core pertenece a la calse core y running empieza true
    renderer = std::make_unique<Renderer>(800, 600, "Platformer");
    inputManager = std::make_unique<InputManager>();
    physics = std::make_unique<Physics>(1200.0f); //gravedad

    // Inicializamos al jugador
    player.x = 100;
    player.y = 100;
    player.vx = 0;
    player.vy = 0;
    player.width = 50;
    player.height = 50;
    player.grounded = false;
}

// destructor
Core::~Core() {}

// game loop (60 veces por segundo)
void Core::run() {
    // Variables para calcular el tiempo (Delta Time)
    Uint64 lastTime = SDL_GetTicks();
    Uint64 currentTime;

    while (running) {
        // calcular dt
        currentTime = SDL_GetTicks();
        // Convertimos milisegundos a segundos
        float dt = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        // inputs
        running = inputManager->processInput();

        // Controlamos la velocidad (vx)
        player.vx = 0; // Frenamos si no hay teclas

        if (inputManager->isKeyPressed(SDLK_D)) {
            player.vx = 300.0f; // Mover derecha
        }
        if (inputManager->isKeyPressed(SDLK_A)) {
            player.vx = -300.0f; // Mover izquierda
        }
        // Salto, solo si estamos en el suelo (grounded)
        // saltar es restar "Y" SDL
        if (inputManager->isKeyPressed(SDLK_W) && player.grounded) {
            player.vy = -600.0f; // Impulso hacia arriba
            player.grounded = false; 
        }

        //actualizamos la fisica
        // gravedad + colisión suelo
        physics->update(player, dt);

        renderer->clear(); // limpiamos
        renderer->drawRect(player.x, player.y, player.width, player.height); // dibujames en base a las coordenadas de physics
        renderer->present(); // presentamos lo nuevo
    }
}