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

    // --- ANIMACIONES ---
    std::vector<SDL_Texture*> idleAnim;
    std::vector<SDL_Texture*> runAnim;
    std::vector<SDL_Texture*> jumpAnim;
    std::vector<SDL_Texture*> doubleJumpAnim;

    //fondo
    SDL_Texture* backgroundTexture;

    // platafomas
    std::vector<Platform> platforms; // Lista de datos físicos
    SDL_Texture* bigPlatform;
    SDL_Texture* smallPlatform;

    // Variables de control
    std::vector<SDL_Texture*>* currentAnim; // Puntero a la animación actual
    float frameTimer;       // Contador de tiempo para cambiar imagen
    int currentFrame;       // Índice de la imagen actual (0, 1, 2...)
    bool facingLeft;        // ¿Mira a la izquierda?

    bool running;
};
#endif