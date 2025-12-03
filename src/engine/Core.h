#pragma once
#include <memory>
#include "Renderer.h"
#include "InputManager.h"
#include "Physics.h"
#include "Player.h" 
#include "Level.h"  

class Core {
public:
    Core();
    ~Core();
    void run();

private:
    void update(float dt);
    void render();

    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<InputManager> inputManager;
    std::unique_ptr<Physics> physics;

    // objetos propios
    std::unique_ptr<Player> player; 
    std::unique_ptr<Level> level;

    bool running;
};