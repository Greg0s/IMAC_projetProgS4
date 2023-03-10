#include "./Boid.hpp"

glm::vec2 Boid::getPosition()
{
    return pos;
}

// float Boid::separationForce()
// {
//     float totalForce = 0;
// }

std::vector<Boid> Boid::getNearBoids(std::vector<Boid> boids, uint boid)
{
    std::vector<Boid> nearBoids;

    float boidX = boids.at(boid).getPosition().x;
    float boidY = boids.at(boid).getPosition().y;
    for (uint i = 0; i < boids.size(); i++)
    {
        float currentX = boids.at(i).getPosition().x;
        float currentY = boids.at(i).getPosition().y;

        if (currentX < (boidX + 0.1) || currentX > (boidX - 0.1) || currentY > (boidY - 0.1) || currentY < (boidY + 0.1))
        {
            nearBoids.push_back(boids.at(i));
        }
    }
}

// glm::vec2 getCenter(std::vector<Boid::Boid> boids)
// {
// }