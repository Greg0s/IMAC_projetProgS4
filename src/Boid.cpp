#include "./Boid.hpp"
#include "glm/ext/quaternion_geometric.hpp"

glm::vec2 Boid::getPosition() const
{
    return pos;
}

glm::vec2 Boid::getDirection() const
{
    return dir;
}

glm::vec2 Boid::getSpeed() const
{
    return v;
}

void Boid::printBoid() const
{
    std::cout << "-------BOID----------" << std::endl;
    std::cout << "Pos: x " << pos.x << " y " << pos.y << std::endl;
    std::cout << "Dir: x " << dir.x << " y " << dir.y << std::endl;
    std::cout << "v: x " << v.x << " y " << v.y << std::endl;
}

float Boid::getX() const
{
    return pos.x;
}
float Boid::getY() const
{
    return pos.y;
}

void Boid::setPosition(const glm::vec2& newPos)
{
    pos.x = newPos.x;
    pos.y = newPos.y;
}

void Boid::setDirectionX(const float& dirX)
{
    dir.x = dirX;
}

void Boid::setDirectionY(const float& dirY)
{
    dir.y = dirY;
}

void Boid::move()
{
    pos += dir * v;
}

// void Boid::inSquare(const float& squareSize, const float& size, const float& strength)
// {

// }

void Boid::inSquare(const float& squareSize, const float& size, const float& strength, const float& scope)
{
    // if (pos.x > squareSize - size || pos.x < -squareSize + size)
    // {
    //     dir.x = -dir.x;
    // }
    // if (pos.y > squareSize - size || pos.y < -squareSize + size)
    // {
    //     dir.y = -dir.y;
    // }

    glm::vec2   boundsForce = {0., 0.};
    const float maxX        = 1;
    const float maxY        = 1;
    const float minX        = -1;
    const float minY        = -1;

    if (pos.x > squareSize - size - scope)
    {
        boundsForce.x = -glm::distance(pos.x, maxX) * (maxX / pos.x);
    }
    if (pos.x < -squareSize + size + scope)
    {
        boundsForce.x = glm::distance(pos.x, minX) * (minX / pos.x);
    }
    if (pos.y > squareSize - size - scope)
    {
        boundsForce.y = -glm::distance(pos.y, maxY) * (maxY / pos.y);
    }
    if (pos.y < -squareSize + size + scope)
    {
        boundsForce.y = glm::distance(pos.y, minY) * (minY / pos.y);
    }

    dir += boundsForce * strength;
    dir = glm::normalize(dir);
}

std::vector<Boid> Boid::getNearBoids(const std::vector<Boid>& boids, float scope)
{
    std::vector<Boid> nearBoids;

    for (const auto& boid : boids)
    {
        // to not count itself
        if (this == &boid)
            continue;

        const float distance = glm::distance(pos, boid.getPosition());

        if (distance > scope)
        {
            nearBoids.push_back(boid);
        }
    }
    return nearBoids;
}

void Boid::separationForce(const std::vector<Boid>& boids, float scope, float strength)
{
    glm::vec2         totalForce = {0., 0.};
    std::vector<Boid> nearBoids  = getNearBoids(boids, scope);

    if (!nearBoids.empty())
    {
        for (auto nearBoid : nearBoids)
        {
            totalForce += (pos - nearBoid.getPosition()) / glm::distance(pos, nearBoid.getPosition());
        }

        totalForce /= nearBoids.size();
        dir += totalForce * strength;
        dir = glm::normalize(dir);
    }
}

void Boid::alignementForce(const std::vector<Boid>& boids, const float& scope, const float& strength)
{
    glm::vec2         averageDirection = {0., 0.};
    std::vector<Boid> nearBoids        = getNearBoids(boids, scope);

    if (!nearBoids.empty())
    {
        for (auto nearBoid : nearBoids)
        {
            averageDirection += nearBoid.getDirection();
        }

        averageDirection /= nearBoids.size();
        dir += averageDirection * strength;
        dir = glm::normalize(dir);
    }
}

void Boid::cohesionForce(const std::vector<Boid>& boids, const float& scope, const float& strength)
{
    glm::vec2         averagePosition = {0.0, 0.0};
    std::vector<Boid> nearBoids       = getNearBoids(boids, scope);

    if (!nearBoids.empty())
    {
        for (auto nearBoid : nearBoids)
        {
            averagePosition /= nearBoid.getPosition();
        }
        averagePosition /= nearBoids.size();
        dir += averagePosition * strength;
        dir = glm::normalize(dir);
    }
}