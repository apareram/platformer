#include "Player.h"
#include "ResourceManager.h" // Usamos el nuevo manager

Player::Player(Renderer* renderer) : currentFrame(0), frameTimer(0), facingLeft(false) {
    // se inicializam Físicas
    body.x = 100; body.y = 100;
    body.width = 40; body.height = 80;
    body.vx = 0; body.vy = 0;
    body.grounded = false;

    // se cargan Sprites usando el ResourceManager
    SDL_Renderer* rawRen = renderer->getRenderer(); // se necesita SDL_Renderer crudo para cargar
    auto& res = ResourceManager::getInstance();
    // cargamos animaciones
    idleAnim.push_back(res.loadTexture("assets/monoIdle.png", rawRen));
    runAnim.push_back(res.loadTexture("assets/monoCorriendo1.png", rawRen));
    runAnim.push_back(res.loadTexture("assets/monoCorriendo2.png", rawRen));
    runAnim.push_back(res.loadTexture("assets/monoCorriendo3.png", rawRen));
    // salto
    jumpAnim.push_back(res.loadTexture("assets/monoSaltando.png", rawRen));
    //doble salto
    doubleJumpAnim.push_back(res.loadTexture("assets/monoRotando1.png", rawRen));
    doubleJumpAnim.push_back(res.loadTexture("assets/monoRotando2.png", rawRen));
    doubleJumpAnim.push_back(res.loadTexture("assets/monoRotando3.png", rawRen));
    doubleJumpAnim.push_back(res.loadTexture("assets/monoRotando4.png", rawRen));
    // Empezamos parados
    currentAnim = &idleAnim;
}

void Player::handleInput(InputManager* input) {
    static bool jumpKeyPressed = false;
    
    // se resetea velocidad X
    body.vx = 0; // se frena si no hay teclas
    if (input->isKeyPressed(SDLK_D)) body.vx = SPEED;
    if (input->isKeyPressed(SDLK_A)) body.vx = -SPEED;

    // lógica de Salto (saltar es restar "Y" SDL)
    bool currentJumpKey = input->isKeyPressed(SDLK_W);
    if (currentJumpKey && !jumpKeyPressed) { // si esta en el suelo o menos de 2 saltos
        if (body.grounded || body.jumpCount < 2) {
            body.vy = JUMP_FORCE; // impulso
            body.grounded = false;
            body.jumpCount++; // se suma saltos
        }
    }
    jumpKeyPressed = currentJumpKey;
}

void Player::update(float dt) {
    // animación
    // se determina dirección
    if (body.vx > 0) facingLeft = false;
    if (body.vx < 0) facingLeft = true;

    // estados de animación
    std::vector<SDL_Texture*>* nextAnim = &idleAnim; // por defecto Idle
    float animSpeed = 0.1f; // velocidad normal (100ms por frame)

    if (body.grounded) {
        if (body.vx != 0) {
            nextAnim = &runAnim;
            animSpeed = 0.1f; // correr
        } else {
            nextAnim = &idleAnim;
        }
    } else {
        // doble salto
        if (body.jumpCount >= 2) {
            nextAnim = &doubleJumpAnim;
            animSpeed = 0.05f; // el giro debe ser rápido (50ms)
        } else {
            nextAnim = &jumpAnim;
        }
    }

    // cambio de animacion
    if (currentAnim != nextAnim) {
        currentAnim = nextAnim;
        currentFrame = 0; // se reinicia la animación desde el principio
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
        currentFrame = 0; // si es imagen única
    }
}

void Player::render(Renderer* renderer) {
    // lógica de dibujo desplazado
    SDL_Texture* tex = (*currentAnim)[currentFrame];
    
    // ajuste visual (100x100 vs 40x80)
    float drawW = 100; float drawH = 100;
    float drawX = body.x - (drawW - body.width) / 2;
    float drawY = body.y - (drawH - body.height);

    renderer->drawTexture(tex, drawX, drawY, drawW, drawH, facingLeft);
}