#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <string>

class Renderer {
private:
    SDL_Window* window;         // Ventana principal
    SDL_Renderer* renderer;     // Renderer de SDL para dibujar en la ventana
public:
    Renderer(int width, int height, const std::string& title);  // Constructor
    ~Renderer();                                                  // Destructor

    void clear();             // Limpia la pantalla con un color predeterminado
    void present();           // Presenta el contenido renderizado en pantalla
    SDL_Renderer* getRenderer();  // Devuelve el renderer interno de SDL (para dibujar sprites)
};

#endif
