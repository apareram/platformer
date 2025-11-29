#ifndef CORE_H
#define CORE_H

#include <memory>
#include "Renderer.h"
#include "InputManager.h"

class Core {

    public:
    Core();
    ~Core();

    void run();

    private:
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<InputManager> inputManager;
    bool running;
};
#endif