#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include <string>

class Renderer {
public:
    Renderer(int width, int height, const std::string& title);
    ~Renderer();

    void clear();
    void present();
    void drawRect(float x, float y, float w, float h); // funcion para dibujar un rectangulo de prueba
    SDL_Renderer* getRenderer(); // Return raw SDL pointer

private:
    SDL_Window* window;      // SDL3 uses raw pointers
    SDL_Renderer* renderer;  // SDL3 uses raw pointers
};

#endif