#include "Physics.h"

Physics::Physics(float gravity, float groundLevel) : gravity(gravity), groundLevel(groundLevel){}

void Physics::update(Body& body, float dt) {
    // se aplica gravedad
    body.vy += gravity * dt;

    // se intrgra la velocidad
    body.x += body.vx * dt;
    body.y += body.vy * dt;

    // rotación
    body.angle += body.angularVel * dt;

    // sencilla colicion con el piso
    if (body.y + body.height >= groundLevel) {
        body.y = groundLevel - body.height;
        body.vy = 0;
        body.grounded = true;
        // REINICIAMOS SALTOS Y ROTACIÓN AL TOCAR EL SUELO
        body.jumpCount = 0;
        body.angularVel = 0;
    } else {
        body.grounded = false;
    }
}