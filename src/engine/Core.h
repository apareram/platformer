#ifndef CORE_H
#define CORE_H

#include <memory>
#include "Renderer.h"
#include "InputManager.h"

// se define la clase core
class Core {

    public:
    Core();
    ~Core(); //destrucor (limpiador)

    void run(); //bucle del juego

    private:
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<InputManager> inputManager;
    bool running;
};
#endif