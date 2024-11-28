#include <SDL2/SDL.h>
#include <iostream>
#include "Renderer.h"
#include "InputManager.h"

class Core {
public:
    void run() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
            return;
        }

        Renderer renderer(800, 600, "Mi Videojuego");
        InputManager inputManager;

        bool running = true;
        while (running) {
            // Manejar eventos
            running = inputManager.processInput();

            // Lógica del juego (aquí añadirás updates)
            // ...

            // Dibujar la escena
            renderer.clear();
            // renderer.draw(player, enemigos, etc.);
            renderer.present();
        }

        SDL_Quit();
    }
};