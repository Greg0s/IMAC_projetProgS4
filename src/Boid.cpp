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

void Boid::showBoid()
{
    std::cout << "-------BOID----------" << std::endl;
    std::cout << "Pos: x " << pos.x << " y " << pos.y;
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

// void Boid::separation(std::vector<Boid> boids, uint boidNum)
// {
//     Boid        boid        = boids.at(boidNum);
//     const float avoidFactor = 0.05;

//     glm::vec2 dir = {0.f, 0.f};
//     for (uint i = 0; i < boids.size(); i++)
//     {
//         if (i != boidNum)
//         {
//             if (isNear(boid))
//             {
//                 dir.x += boid.pos.x - boids.at(i).getX();
//                 dir.y += boid.pos.y - boids.at(i).getY();
//             }
//         }
//     }

//     boid.dir.x = dir.x * avoidFactor;
//     boid.dir.y = dir.y * avoidFactor;
// }

// bool Boid::isNear(Boid boid)
// {
//     const float minDistance = 0.1;

//     float currentX = boid.getX();
//     float currentY = boid.getY();
//     float boidX    = this->getX();
//     float boidY    = this->getY();

//     return currentX < (boidX + minDistance) || currentX > (boidX - minDistance) || currentY > (boidY - minDistance) || currentY < (boidY + minDistance);
// }

glm::vec2 Boid::separationForce(std::vector<Boid> boids, uint boid)
{
    glm::vec2 totalForce = {0, 0};

    glm::vec2 boidPos = boids.at(boid).getPosition();

    std::vector<Boid> nearBoids = getNearBoids(boids, boid);
    for (auto nearBoid : nearBoids)
    {
        totalForce.x += boidPos.x - nearBoid.getPosition().x;
        totalForce.y += boidPos.y - nearBoid.getPosition().y;
    }
    return totalForce;
}

std::vector<Boid> Boid::getNearBoids(std::vector<Boid> boids, uint boid)
{
    std::vector<Boid> nearBoids;

    const float minDistance = 0.1;

    float boidX = boids.at(boid).getPosition().x;
    float boidY = boids.at(boid).getPosition().y;
    for (uint i = 0; i < boids.size(); i++)
    {
        float currentX = boids.at(i).getPosition().x;
        float currentY = boids.at(i).getPosition().y;

        if (currentX < (boidX + minDistance) || currentX > (boidX - minDistance) || currentY > (boidY - minDistance) || currentY < (boidY + minDistance))
        {
            nearBoids.push_back(boids.at(i));
        }
    }
    return nearBoids;
}

// glm::vec2 getCenter(std::vector<Boid::Boid> boids)
// {
// }