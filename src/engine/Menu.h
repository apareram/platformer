#pragma once
#include "Renderer.h"
#include "InputManager.h"
#include <SDL3/SDL.h>

class Menu {
public:
    Menu(Renderer* renderer);
    
    // devuelve true si el jugador presiona ENTER
    bool handleInput(InputManager* input);
    
    void render(Renderer* renderer);

private:
    SDL_Texture* titleTexture;
    SDL_Texture* startMsgTexture;
    
    // para que el texto "Press Enter" parpade
    float timer;
    bool showText;
};