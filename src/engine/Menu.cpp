#include "Menu.h"
#include "ResourceManager.h"

Menu::Menu(Renderer* renderer) : timer(0), showText(true) {
    auto& res = ResourceManager::getInstance();
    SDL_Renderer* raw = renderer->getRenderer();
    
    titleTexture = res.loadTexture("assets/tituloMenu.png", raw);
    startMsgTexture = res.loadTexture("assets/pressEnter.png", raw);
}

bool Menu::handleInput(InputManager* input) {
    // si se presiona ENTER, el juego inicia
    if (input->isKeyPressed(SDLK_RETURN)) {
        return true; 
    }
    return false;
}

void Menu::render(Renderer* renderer) {
    // efecto de parpadeo para el texto "Start"
    timer += 0.05f; // velocidad del parpadeo
    if (timer > 1.0f) {
        showText = !showText;
        timer = 0;
    }

    // se dibuja el título (arriba centrado)
    if (titleTexture)
        renderer->drawTexture(titleTexture, 200, 100, 400, 150, false);

    // se dibuja "Press Enter" (abajo)
    if (startMsgTexture && showText)
        renderer->drawTexture(startMsgTexture, 250, 400, 300, 50, false);
}