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
    Platform p1 = {65, 65, 250, 120};   // La grande
    Platform p2 = {400, 300, 100, 100}; // La pequeña
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
                // OJO: Para el doble salto quizás no quieras loop, pero por ahora dejémoslo así
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
        renderer->drawTexture(bigPlatform, 65, 65, 250, 120, false);
        renderer->drawTexture(smallPlatform, 400, 300, 100, 100, false);

        // Obtenemos la textura actual
        SDL_Texture* textureToDraw = (*currentAnim)[currentFrame];
        
        float drawWidth = 100.0f;
        float drawHeight = 100.0f;
        // Offset X: Centramos la imagen sobre el cuerpo físico
        float drawX = player.x - (drawWidth - player.width) / 2;
        // Offset Y: Alineamos la base de la imagen con los pies del cuerpo físico
        // (Restamos la diferencia de altura para que la imagen suba un poco)
        float drawY = player.y - (drawHeight - player.height);

        // Dibujamos el sprite en lugar del rectángulo
        renderer->drawTexture(textureToDraw, drawX, drawY, drawWidth, drawHeight, facingLeft);

        // --- MODO DEBUG: DIBUJAR LAS CAJAS INVISIBLES ---
        // 1. Dibujar hitbox del jugador (VERDE)
        SDL_SetRenderDrawColor(renderer->getRenderer(), 0, 255, 0, 255); // Verde
        SDL_FRect playerRect = {player.x, player.y, player.width, player.height};
        SDL_RenderRect(renderer->getRenderer(), &playerRect); // Dibuja solo el borde

        // 2. Dibujar hitboxes de las plataformas (ROJO)
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