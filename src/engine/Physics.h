#pragma once
#include <SDL3/SDL.h>

struct Body {
    float x, y;
    float vx, vy;
    float width, height;
    bool grounded = false;
    int jumpCount = 0;       
    float angle = 0.0f;      
    float angularVel = 0.0f;
};

class Physics {
public:
    Physics(float gravity = 1200.0f, float groundLevel = 600.0f);
    void update(Body& body, float dt);
private:
    float gravity;
    float groundLevel;
};