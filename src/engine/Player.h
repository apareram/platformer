#pragma once
#include "Physics.h"      // acceso a struct Body
#include "Renderer.h"     // dibujar
#include "InputManager.h" // leer teclas
#include <vector>

class Player {
public:
    Player(Renderer* renderer); // constructor carga sus propios sprites
    
    void handleInput(InputManager* input);
    void update(float dt);
    void render(Renderer* renderer);

    // Ggtters para que la física externa pueda moverlo
    Body& getBody() { return body; }

private:
    Body body;
    
    // animaciones internas
    std::vector<SDL_Texture*> idleAnim;
    std::vector<SDL_Texture*> runAnim;
    std::vector<SDL_Texture*> jumpAnim;
    std::vector<SDL_Texture*> doubleJumpAnim;
    
    // estado de animación
    std::vector<SDL_Texture*>* currentAnim;
    int currentFrame;
    float frameTimer;
    bool facingLeft;
    
    // constantes propias del jugador
    const float SPEED = 350.0f;
    const float JUMP_FORCE = -650.0f;
};