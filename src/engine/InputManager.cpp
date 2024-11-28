#include <SDL2/SDL.h>

class InputManager {
public:
    bool processInput() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return false;
            }
            // Maneja más input aquí (teclado, ratón, etc.)
        }
        return true;
    }
};