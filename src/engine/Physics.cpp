#include "Physics.h"

Physics::Physics(float gravity) : gravity(gravity) {}

void Physics::update(Body& body, float dt) {
    // se aplica gravedad
    body.vy += gravity * dt;

    // se intrgra la velocidad
    body.x += body.vx * dt;
    body.y += body.vy * dt;

    // sencilla colicion con el piso a y = 400
    if (body.y + body.height >= 400) {
        body.y = 400 - body.height;
        body.vy = 0;
        body.grounded = true;
    } else {
        body.grounded = false;
    }
}