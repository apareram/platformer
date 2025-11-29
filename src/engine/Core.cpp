#include "Core.h"

Core::Core() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        throw std::runtime_error("Error al inicializar SDL");
    }
    renderer = new Renderer(800, 600, "Game");
    inputManager = new InputManager();
    running = true;
}

Core::~Core() {
    delete renderer;
    delete inputManager;
    SDL_Quit();
}

void Core::run() {
    while (running) {
        // Procesa entradas
        running = inputManager->processInput();

        // Actualiza lógica del juego (aquí se añadirá más contenido en futuros capí
        // ...

        // Renderiza escena
        renderer->clear();
        // renderer->draw(...); // Ejemplo: dibujar objetos aquí
        renderer->present();
    }
}