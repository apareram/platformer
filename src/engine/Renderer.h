#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include <string>

class Renderer {
public:
    Renderer(int width, int height, const std::string& title);  // Constructor
    ~Renderer();                                                  // Destructor

    void clear();             // Limpia la pantalla con un color predeterminado
    void present();           // Presenta el contenido renderizado en pantalla
    std::unique_ptr<Renderer> getRenderer();  // Devuelve el renderer interno de SDL (para dibujar sprites)

    private:
    std::unique_ptr<Window> window;         // Ventana principal
    std::unique_ptr<Renderer> renderer;     // Renderer de SDL para dibujar en la ventana
};

#endif