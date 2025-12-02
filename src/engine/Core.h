#ifndef CORE_H
#define CORE_H

#pragma once
#include <memory>
#include "Renderer.h"
#include "InputManager.h"
#include "Physics.h"

// se define la clase core
class Core {

    public:
    Core();
    ~Core(); //destrucor (limpiador)

    void run(); //bucle del juego

    private:
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<InputManager> inputManager;
    std::unique_ptr<Physics> physics;

    Body player; // el objeto del jugador
    bool running;
};
#endif