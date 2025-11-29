#include "Physics.h"

Physics::Physics(float gravity) : gravity(gravity) {}

void Physics::update(Body& body, float dt) {
    // Apply gravity
    body.vy += gravity * dt;

    // Integrate velocity
    body.x += body.vx * dt;
    body.y += body.vy * dt;

    // Simple floor collision at y = 400
    if (body.y + body.height >= 400) {
        body.y = 400 - body.height;
        body.vy = 0;
        body.grounded = true;
    } else {
        body.grounded = false;
    }
}