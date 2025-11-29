#ifndef CORE_H
#define CORE_H

#include <memory>
#include "Renderer.h"
#include "InputManager.h"

class Core {
private:
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<InputManager> inputManager;
    bool running;

public:
    Core();
    ~Core();

    void run();
};

#endif