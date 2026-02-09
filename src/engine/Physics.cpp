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

    // --- colision con el piso ---
    if (body.y + body.height >= groundLevel) {
        body.y = groundLevel - body.height;
        body.vy = 0;
        body.grounded = true;
        // see reinician valores al tocar suelo
        body.jumpCount = 0;
        body.angularVel = 0;
    }

    // --- colision con plataformas ---
    if (body.vy >= 0) { // solo si cae, permite saltar "a través"
        for (const auto& plat : platforms) {
            // si estamos en x
            if (body.x + body.width > plat.x + 5 && body.x < plat.x + plat.w - 5) {//con margen de 5px para que no caiga si está justo en el borde
                
                // si los pies están por debajo del techo y
                // si los pies cruzaron el borde de la plataforma, pero no han bajado más de 25 píxeles
                if (body.y + body.height >= plat.y && body.y + body.height <= plat.y + 25.0f) {// si estamos en y

                    body.y = plat.y - body.height; 
                    body.vy = 0;
                    body.grounded = true;
                    body.jumpCount = 0; // Reset saltos
                    body.angularVel = 0;
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

bool Physics::checkPortalCollision(const Body& body, const Portal& portal) {
    return (
        body.x < portal.x + portal.w &&
        body.x + body.width > portal.x &&
        body.y < portal.y + portal.h &&
        body.y + body.height > portal.y
    );
}