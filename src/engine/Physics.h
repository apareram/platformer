#pragma once
#include <SDL2/SDL.h>

struct Body {
    float x, y;
    float vx, vy;
    float width, height;
    bool grounded = false;
};

class Physics {
public:
    Physics(float gravity = 1200.0f);
    void update(Body& body, float dt);
private:
    float gravity;
};