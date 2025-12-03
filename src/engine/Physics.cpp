#include "Physics.h"

Physics::Physics(float gravity, float groundLevel) : gravity(gravity), groundLevel(groundLevel){}

void Physics::update(Body& body, float dt, const std::vector<Platform>& platforms) {
    // se aplica gravedad
    body.vy += gravity * dt;

    // se intrgra la velocidad
    body.x += body.vx * dt;
    body.y += body.vy * dt;

    // rotación
    body.angle += body.angularVel * dt;

    // cuerpo cae hasta que se demuetre lo contrario
    body.grounded = false;

    // sencilla colicion con el piso
    if (body.y + body.height >= groundLevel) {
        body.y = groundLevel - body.height;
        body.vy = 0;
        body.grounded = true;
        // REINICIAMOS SALTOS Y ROTACIÓN AL TOCAR EL SUELO
        body.jumpCount = 0;
        body.angularVel = 0;
    }

    // --- COLISIÓN CON PLATAFORMAS ---
    // Solo checamos colisión si estamos cayendo (vy > 0)
    // Esto permite saltar "a través" de ellas desde abajo (tipo Mario Bros)
    if (body.vy >= 0) {
        for (const auto& plat : platforms) {
            if (checkCollision(body, plat)) {
                
                // Verificamos si los pies estaban "arriba" de la plataforma antes de chocar
                // (Para evitar que te teletransportes al techo si saltas de lado)
                float previousFootY = body.y + body.height - (body.vy * dt);
                
                if (previousFootY <= plat.y + 10.0f) { // +10 es un margen de error
                    body.y = plat.y - body.height; // Te subo a la plataforma
                    body.vy = 0;
                    body.grounded = true;
                    body.jumpCount = 0;
                    body.angularVel = 0;
                    // body.angle = 0; // Enderezar
                }
            }
        }
    }
}

// Función auxiliar: Detecta si dos rectángulos se tocan (AABB)
bool Physics::checkCollision(const Body& b, const Platform& p) {
    return (
        b.x < p.x + p.w &&      // Izquierda del cuerpo < Derecha plat
        b.x + b.width > p.x &&  // Derecha cuerpo > Izquierda plat
        b.y < p.y + p.h &&      // Cabeza cuerpo < Pies plat
        b.y + b.height > p.y    // Pies cuerpo > Cabeza plat
    );
}