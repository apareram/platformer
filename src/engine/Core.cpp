#include "Core.h"
#include <stdexcept>

// constructor
Core::Core() : running(true){ // funcion core pertenece a la calse core y running empieza true
    renderer = std::make_unique<Renderer>(800, 600, "Game");
    inputManager = std::make_unique<InputManager>();
}

// destructor
Core::~Core() {
}

// game loop (60 veces por segundo)
void Core::run() {
    while (running) {
        running = inputManager->processInput();
        // aquí se añadira la física del juego y los objetos
        renderer->clear();
        renderer->present();
    }
}