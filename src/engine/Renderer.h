#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h> 
#include <vector>
#include <string>

class Renderer {
public:
    Renderer(int width, int height, const std::string& title);
    ~Renderer();

    void clear();
    void present();
    SDL_Texture* loadTexture(const std::string& path); // carga una imagen y devolver un puntero
    SDL_Renderer* getRenderer(); // Return raw SDL pointer
    void drawTexture(SDL_Texture* texture, float x, float y, float w, float h, bool flipX); // Dibuja una textura completa

private:
    SDL_Window* window;      // SDL3 uses raw pointers
    SDL_Renderer* renderer;  // SDL3 uses raw pointers
};

#endif