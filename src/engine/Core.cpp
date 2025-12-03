#include "Core.h"
#include <stdexcept>
#include <iostream>

// constructor
Core::Core() : running(true){ // funcion core pertenece a la clase core y running empieza true
    renderer = std::make_unique<Renderer>(800, 600, "Platformer");
    inputManager = std::make_unique<InputManager>();
    physics = std::make_unique<Physics>(1200.0f, 520.0f); //gravedad

    // inicializamos al jugador
    player.x = 100;
    player.y = 100;
    player.vx = 0;
    player.vy = 0;
    player.width = 40;
    player.height = 80;
    player.grounded = false;

    // cargar el fondo
    backgroundTexture = renderer->loadTexture("assets/fondo.png");

    // cargar plataformas
    bigPlatform = renderer->loadTexture("assets/plataformaGrande.png");
    smallPlatform = renderer->loadTexture("assets/platafomaPequena.png");
    Platform p1 = {55, 85, 250, 100};   // La grande
    Platform p2 = {400, 330, 100, 80}; // La pequeña
    platforms.push_back(p1);
    platforms.push_back(p2);

    // cargamks sprites
    idleAnim.push_back(renderer->loadTexture("assets/monoIdle.png"));

    runAnim.push_back(renderer->loadTexture("assets/monoCorriendo1.png"));
    runAnim.push_back(renderer->loadTexture("assets/monoCorriendo2.png"));
    runAnim.push_back(renderer->loadTexture("assets/monoCorriendo3.png"));

    jumpAnim.push_back(renderer->loadTexture("assets/monoSaltando.png"));

    //doble salto
    doubleJumpAnim.push_back(renderer->loadTexture("assets/monoRotando1.png"));
    doubleJumpAnim.push_back(renderer->loadTexture("assets/monoRotando2.png"));
    doubleJumpAnim.push_back(renderer->loadTexture("assets/monoRotando3.png"));
    doubleJumpAnim.push_back(renderer->loadTexture("assets/monoRotando4.png"));

    // Empezamos parados
    currentAnim = &idleAnim;
}

// destructor
Core::~Core() {}

// game loop (60 veces por segundo)
void Core::run() {
    // Variables para calcular el tiempo (Delta Time)
    Uint64 lastTime = SDL_GetTicks();
    Uint64 currentTime;

    // Variable estática para detectar "pulsación única" de tecla
    static bool jumpKeyPressed = false;

    while (running) {
        // calcular dt
        currentTime = SDL_GetTicks();
        // Convertimos milisegundos a segundos
        float dt = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        // inputs
        running = inputManager->processInput();
        
        // Controlamos la velocidad (vx)
        player.vx = 0; // Frenamos si no hay teclas
        if (inputManager->isKeyPressed(SDLK_D)) {
            player.vx = 300.0f; // Mover derecha
        }
        if (inputManager->isKeyPressed(SDLK_A)) {
            player.vx = -300.0f; // Mover izquierda
        }
        // Salto, solo si estamos en el suelo (grounded)
        // saltar es restar "Y" SDL
        // salto y doble salto 
        bool currentJumpKey = inputManager->isKeyPressed(SDLK_W);
        // Solo entramos si acabamos de pulsar la tecla (no si la mantenemos)
        if (currentJumpKey && !jumpKeyPressed) {
            // Permitimos saltar si estamos en el suelo O llevamos menos de 2 saltos
            if (player.grounded || player.jumpCount < 2) {
                player.vy = -600.0f; // Impulso
                player.grounded = false;
                player.jumpCount++;  // Sumamos salto (1 o 2)
                std::cout << "Salto numero: " << player.jumpCount << std::endl;
            }
        }
        jumpKeyPressed = currentJumpKey; // Actualizamos estado de tecla

        //actualizamos la fisica
        // gravedad + colisión suelo
        physics->update(player, dt, platforms);

        // animación
        // determinamos dirección
        if (player.vx > 0) facingLeft = false;
        if (player.vx < 0) facingLeft = true;

        // estados de animación
        std::vector<SDL_Texture*>* nextAnim = &idleAnim; // Por defecto Idle
        float animSpeed = 0.1f; // Velocidad normal (100ms por frame)

        if (player.grounded) {
            if (player.vx != 0) {
                nextAnim = &runAnim;
                animSpeed = 0.1f; // Correr
            } else {
                nextAnim = &idleAnim;
            }
        } else {
            // doble salto
            if (player.jumpCount >= 2) {
                nextAnim = &doubleJumpAnim;
                animSpeed = 0.05f; // El giro debe ser rápido (50ms)
            } else {
                nextAnim = &jumpAnim;
            }
        }

        // cambio de animacion
        if (currentAnim != nextAnim) {
            currentAnim = nextAnim;
            currentFrame = 0; // Reiniciar animación desde el principio
            frameTimer = 0;
        }

        // avance de frames
        if (currentAnim->size() > 1) {
            frameTimer += dt;
            if (frameTimer >= animSpeed) {
                currentFrame++;
                frameTimer = 0;
                
                // loop
                if (currentFrame >= currentAnim->size()) {
                    currentFrame = 0;
                }
            }
        } else {
            currentFrame = 0; // Si es imagen única
        }

        renderer->clear(); // limpiamos

        // dibujamos el fondo (siempre antes que el jugados)
        if (backgroundTexture) {
            renderer->drawTexture(backgroundTexture, 0, 0, 800, 600, false);
        }

        // dibujamos plataformas
        renderer->drawTexture(bigPlatform, platforms[0].x, platforms[0].y - 20, platforms[0].w, 120, false);
        renderer->drawTexture(smallPlatform, platforms[1].x, platforms[1].y - 20, platforms[1].w, 100, false);
        
        // jugador
        SDL_Texture* textureToDraw = (*currentAnim)[currentFrame]; //obtenemos textura actual
        float drawWidth = 100.0f;
        float drawHeight = 100.0f;
        float drawX = player.x - (drawWidth - player.width) / 2; // centramos la imagen sobre el cuerpo físico
        float drawY = player.y - (drawHeight - player.height); // lineamos la base de la imagen con los pies del cuerpo físico
        renderer->drawTexture(textureToDraw, drawX, drawY, drawWidth, drawHeight, facingLeft);

        // --- MODO DEBUG: DIBUJAR LAS CAJAS INVISIBLES ---
        // jugador
        SDL_SetRenderDrawColor(renderer->getRenderer(), 0, 255, 0, 255); // Verde
        SDL_FRect playerRect = {player.x, player.y, player.width, player.height};
        SDL_RenderRect(renderer->getRenderer(), &playerRect); // Dibuja solo el borde
        // plataformas
        SDL_SetRenderDrawColor(renderer->getRenderer(), 255, 0, 0, 255); // Rojo
        for(const auto& p : platforms) {
            SDL_FRect platformRect = {p.x, p.y, p.w, p.h};
            SDL_RenderRect(renderer->getRenderer(), &platformRect);
        }
        // Restaurar color negro por seguridad
        SDL_SetRenderDrawColor(renderer->getRenderer(), 0, 0, 0, 255);
        // --------------------------------------------------------------

        renderer->present(); // presentamos lo nuevo
    }
}