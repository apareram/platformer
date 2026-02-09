#pragma once
#include <SDL3/SDL.h>
#include <vector>

struct Body {
    float x, y;
    float vx, vy;
    float width, height;
    bool grounded = false;
    int jumpCount = 0;       
    float angle = 0.0f;      
    float angularVel = 0.0f;
};

struct Platform {
    float x, y, w, h;
};

struct Portal {
    float x, y, w, h;
};

class Physics {
public:
    Physics(float gravity = 1200.0f, float groundLevel = 600.0f);
    void update(Body& body, float dt, const std::vector<Platform>& platforms);
    bool checkPortalCollision(const Body& body, const Portal& portal);
private:
    float gravity;
    float groundLevel;
    bool checkCollision(const Body& b, const Platform& p);
};