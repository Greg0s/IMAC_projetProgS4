#include "p6/p6.h"

class Boid {
private:
    glm::vec2 pos;
    glm::vec2 dir;
    float     v;
    float     a;

public:
    explicit Boid(glm::vec2 position = {0, 0}, float vitesse = 1, glm::vec2 direction = {0, 0}, float acceleration = 0)
        : pos(position), dir(direction), v(vitesse), a(acceleration){};

    glm::vec2 getPosition();
    // float                   separationForce();
    std::vector<Boid> getNearBoids(std::vector<Boid> boids, uint boid);
};