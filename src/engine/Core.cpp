#include "Core.h"
#include <stdexcept>

Core::Core() : running(true){
    renderer = std::make_unique<Renderer>(800, 600, "Game");
    inputManager = std::make_unique<InputManager>();
    running = true;
}

Core::~Core() {
}

void Core::run() {
    while (running) {
        running = inputManager->processInput();
        // aquí se añadira la física del juego y los objetos
        renderer->clear();
        renderer->present();
    }
}