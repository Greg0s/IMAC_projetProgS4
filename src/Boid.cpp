#include "./Boid.hpp"

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

void Boid::inSquare(const float& squareSize, const float& size, const float& strength)
{
    if (pos.x > squareSize - size || pos.x < -squareSize + size)
    {
        dir.x = strength * -dir.x;
    }
    if (pos.y > squareSize - size || pos.y < -squareSize + size)
    {
        dir.y = strength * -dir.y;
    }
}

void Boid::separationForce(const std::vector<Boid>& boids, float scope, float strength)
{
    glm::vec2 totalForce = {0, 0};
    uint      count      = 0;

    std::vector<Boid> nearBoids = getNearBoids(boids, scope);
    for (auto nearBoid : nearBoids)
    {
        totalForce += strength * (pos - nearBoid.getPosition()) / glm::distance(pos, nearBoid.getPosition());
        count++;
    }

    if (count > 0)
    {
        totalForce /= static_cast<float>(count);
        dir += totalForce;
        dir = glm::normalize(dir);
    }
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