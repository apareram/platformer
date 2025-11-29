#include "Core.h"
#include <stdexcept>

Core::Core() {
    renderer = std::make_unique<Renderer>(800, 600, "Game");
    inputManager = std::make_unique<InputManager>();
    running = true;
}

Core::~Core() {
    // No need to delete manually — unique_ptr handles it.
}

void Core::run() {
    while (running) {
        running = inputManager->processInput();

        renderer->clear();
        renderer->present();
    }
}