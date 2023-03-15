#include "p6/p6.h"

class Boid {
private:
    glm::vec2 pos;
    glm::vec2 dir;
    glm::vec2 v;
    float     a;

public:
    explicit Boid(glm::vec2 position = {0, 0}, glm::vec2 direction = {0, 0}, glm::vec2 speed = {1, 1}, float acceleration = 0)
        : pos(position), dir(direction), v(speed), a(acceleration){};

    glm::vec2 getPosition() const;
    glm::vec2 getDirection() const;
    glm::vec2 getSpeed() const;
    float     getX() const;
    float     getY() const;

    void setPosition(const glm::vec2& newPos);
    void setDirectionX(const float& dirX);
    void setDirectionY(const float& dirY);

    void showBoid() const;

    glm::vec2         separationForce(std::vector<Boid> boids, uint boid);
    std::vector<Boid> getNearBoids(std::vector<Boid> boids, uint boid);
    void              separation(std::vector<Boid> boids, uint boidNum);
    bool              isNear(Boid boid);
};