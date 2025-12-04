#include "Player.h"
#include "ResourceManager.h" // Usamos el nuevo manager

Player::Player(Renderer* renderer) : currentFrame(0), frameTimer(0), facingLeft(false) {
    // se inicializam Físicas
    body.x = 100; body.y = 100;
    body.width = 40; body.height = 80;
    body.vx = 0; body.vy = 0;
    body.grounded = false;
    isAttacking = false;
    isCrouching = false;

    // se cargan Sprites usando el ResourceManager
    SDL_Renderer* rawRen = renderer->getRenderer(); // se necesita SDL_Renderer crudo para cargar
    auto& res = ResourceManager::getInstance();
    // cargamos animaciones
    idleAnim.push_back(res.loadTexture("assets/monoIdle1.png", rawRen));
    idleAnim.push_back(res.loadTexture("assets/monoIdle2.png", rawRen));
    idleAnim.push_back(res.loadTexture("assets/monoIdle3.png", rawRen));
    idleAnim.push_back(res.loadTexture("assets/monoIdle4.png", rawRen));

    runAnim.push_back(res.loadTexture("assets/monoCorriendo1.png", rawRen));
    runAnim.push_back(res.loadTexture("assets/monoCorriendo2.png", rawRen));
    runAnim.push_back(res.loadTexture("assets/monoCorriendo3.png", rawRen));

    jumpAnim.push_back(res.loadTexture("assets/monoSaltando.png", rawRen));

    doubleJumpAnim.push_back(res.loadTexture("assets/monoRotando1.png", rawRen));
    doubleJumpAnim.push_back(res.loadTexture("assets/monoRotando2.png", rawRen));
    doubleJumpAnim.push_back(res.loadTexture("assets/monoRotando3.png", rawRen));
    doubleJumpAnim.push_back(res.loadTexture("assets/monoRotando4.png", rawRen));

    crouchAnim.push_back(res.loadTexture("assets/monoAgachado1.png", rawRen));
    crouchAnim.push_back(res.loadTexture("assets/monoAgachado2.png", rawRen));
    crouchAnim.push_back(res.loadTexture("assets/monoAgachado3.png", rawRen));
    
    attackAnim.push_back(res.loadTexture("assets/monoAtacando1.png", rawRen));
    attackAnim.push_back(res.loadTexture("assets/monoAtacando2.png", rawRen));
    attackAnim.push_back(res.loadTexture("assets/monoAtacando3.png", rawRen));

    // Empezamos parados
    currentAnim = &idleAnim;
}

void Player::handleInput(InputManager* input) {
    static bool jumpKeyPressed = false;
    isCrouching = false;

    if (isAttacking) return;

    // se resetea velocidad X
    body.vx = 0; // se frena si no hay teclas
    if (input->isKeyPressed(SDLK_D)) body.vx = SPEED;
    if (input->isKeyPressed(SDLK_A)) body.vx = -SPEED;

    // agacharse
    if (input->isKeyPressed(SDLK_S) && body.grounded) {
        isCrouching = true;
        body.vx = 0; // se frena al personaje si se agacha
    }

    // atacar
    static bool spacePressed = false;
    bool currentSpace = input->isKeyPressed(SDLK_SPACE);
    
    if (currentSpace && !spacePressed) {
        // se inicia el ataque
        isAttacking = true;
        currentFrame = 0; // se empieza la animación desde el frame 0
        frameTimer = 0;
    }
    spacePressed = currentSpace;

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
    float animSpeed = 0.5f; // velocidad normal (100ms por frame)
    bool loopAnim = true; // se repite animacion?

    if (isAttacking) {
        // atacar es la prioridad 1
        nextAnim = &attackAnim;
        animSpeed = 0.08f; // el ataque es  rápido
        loopAnim = false;  // el ataque no se repite infinitamente
    }
    else if (body.grounded) {
        if (isCrouching) {
            // agacharse es la prioridad 2
            nextAnim = &crouchAnim;
            animSpeed = 0.15f; 
            loopAnim = false; // se queda en el último frame (agachado total)
        }
        else if (body.vx != 0) {
            nextAnim = &runAnim;
        } else {
            nextAnim = &idleAnim;
            animSpeed = 0.4f;
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
            // finaliza animación
            if (currentFrame >= currentAnim->size()) {
                if (isAttacking) {
                    // si se terminó el ataque, dejamos de atacar y volvemos a Idle
                    isAttacking = false;
                    currentFrame = 0; 
                } 
                else if (isCrouching) {
                    // si se terminó de agacharse, nos quedamos en el último frame (el 2)
                    currentFrame = currentAnim->size() - 1;
                }
                else {
                    // Loop normal (correr, idle, etc)
                    currentFrame = 0;
                }
            }
        }
    } else {
        currentFrame = 0;
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