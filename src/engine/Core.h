#ifndef CORE_H
#define CORE_H

#include "Renderer.h"
#include "InputManager.h"

class Core {
private:
    Renderer* renderer;        // Sistema de renderizado
    InputManager* inputManager;  // Sistema de entrada
    bool running;              // Indica si el juego sigue ejecutándose
public:
    Core();                    // Constructor
    ~Core();                   // Destructor
    void run();                // Ejecuta el bucle principal del juego
};

#endif