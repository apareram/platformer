#include "Renderer.h"
/*
* Constructor de la clase Renderer
* @param width Ancho de la ventana
* @param height Alto de la ventana
* @param title Título de la ventana
*/
Renderer::Renderer(int width, int height, const std::string& title) {
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) throw std::runtime_error("Error al crear la ventana");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) throw std::runtime_error("Error al crear el renderer");
}
/*
* Destructor de la clase Renderer
*/
Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

/*
* Método para limpiar la pantalla
*/
void Renderer::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Negro
    SDL_RenderClear(renderer);
}

/*
*
*/
void Renderer::present() {
    SDL_RenderPresent(renderer);
}

/*
* 
*/
SDL_Renderer* Renderer::getRenderer() {
    return renderer;
}