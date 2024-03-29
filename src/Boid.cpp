#include "./Boid.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/fwd.hpp"

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

void Boid::inSquare(const glm::vec2& squareSize, const float& size, const float& strength, const float& scope)
{
    glm::vec2   boundsForce = {0., 0.};
    const float maxX        = 1;
    const float maxY        = 1;
    const float minX        = -1;
    const float minY        = -1;

    if (pos.x > squareSize.x - size - scope)
    {
        boundsForce.x = -glm::distance(pos.x, maxX) * (pos.x / maxX);
    }
    if (pos.x < -squareSize.x + size + scope)
    {
        boundsForce.x = glm::distance(pos.x, minX) * (minX / pos.x);
    }
    if (pos.y > squareSize.y - size - scope)
    {
        boundsForce.y = -glm::distance(pos.y, maxY) * (pos.y / maxY);
    }
    if (pos.y < -squareSize.y + size + scope)
    {
        boundsForce.y = glm::distance(pos.y, minY) * (minY / pos.y);
    }

    dir += boundsForce * strength;
    dir = glm::normalize(dir);
}

void Boid::separationForce(const std::vector<Boid>& boids, float scope, float strength)
{
    glm::vec2 totalForce = {0., 0.};
    int       count      = 0;

    for (const auto& boid : boids)
    {
        if (this == &boid)
            continue;

        float distance = glm::distance(pos, boid.pos);
        if (distance < scope)
        {
            totalForce += strength * (pos - boid.pos) / distance;
            count++;
        }
    }

    if (count > 0)
    {
        totalForce /= static_cast<float>(count);
        dir += totalForce;
        dir = glm::normalize(dir);
    }
}

void Boid::alignementForce(const std::vector<Boid>& boids, const float& scope, const float& strength)
{
    glm::vec2 averageDirection = {0., 0.};
    float     count            = 0;

    for (const auto& boid : boids)
    {
        if (this == &boid)
            continue;

        const float distance = glm::distance(pos, boid.pos);

        if (distance < scope)
        {
            averageDirection += boid.dir;
            count++;
        }
    }

    if (count > 0)
    {
        averageDirection /= count;
        dir += averageDirection * strength;
        dir = glm::normalize(dir);
    }
}

void Boid::cohesionForce(const std::vector<Boid>& boids, const float& scope, const float& strength)
{
    glm::vec2 averagePosition = {0.0, 0.0};
    float     count           = 0;

    for (const auto& boid : boids)
    {
        if (this == &boid)
            continue;

        const float distance = glm::distance(pos, boid.pos);
        if (distance < scope)
        {
            averagePosition += boid.pos;
            count++;
        }
    }
    if (count > 0)
    {
        averagePosition /= count;
        dir += (averagePosition - pos) * strength;
        dir = glm::normalize(dir);
    }
}