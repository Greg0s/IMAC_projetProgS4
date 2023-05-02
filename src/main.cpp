#include <cstddef>
#include <cstdlib>
#include "glm/fwd.hpp"
#include "p6/p6.h"
// #include <sys/_types/_size_t.h>
#define DOCTEST_CONFIG_IMPLEMENT
#include "Boid.hpp"
#include "doctest/doctest.h"

struct strengths {
    const float boundsStrength     = 1;
    float       separationStrength = 0.04; // 2
    float       alignementStrength = 0.03; // 5
    float       cohesionStrength   = 0.01; // 5
};

struct scopes {
    float       scope     = 0.5;
    const float wallScope = 0.1;
};

void print(float val)
{
    std::cout << val << std::endl;
}

void print(glm::vec2 val)
{
    std::cout << "x: " << val.x << "y: " << val.y << std::endl;
}

glm::vec2 randomPos(glm::vec2 squareSize, float size)
{
    glm::vec2 pos;
    return pos = p6::random::point(
               {
                   -squareSize.x + size,
                   -squareSize.y + size,
               },
               {
                   squareSize.x - size,
                   squareSize.y - size,
               }
           );
}

std::vector<Boid> boidsVec(size_t nbSquare, glm::vec2 squareSize, float size)
{
    std::vector<Boid> boids;

    glm::vec2 pos;
    glm::vec2 direction;
    glm::vec2 speed = {0.008, 0.008};

    // création du vector des boids
    for (size_t i = 0; i < nbSquare; i++)
    {
        // square appears only in the square = center of the square
        pos = randomPos(squareSize, size);

        // squares have a random direction
        direction = p6::random::direction();

        // create the boid of the square i
        Boid boid = Boid(pos, direction, speed);

        // add this boid to the others
        boids.push_back(boid);

        // print pos for debug
        // std::cout << "pos : " << pos.x << " " << pos.y << std::endl;
    }
    return boids;
}

int main(int argc, char* argv[])
{
    { // Run the tests
        if (doctest::Context{}.run() != 0)
            return EXIT_FAILURE;
        // The CI does not have a GPU so it cannot run the rest of the code.
        const bool no_gpu_available =
            argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (no_gpu_available)
            return EXIT_SUCCESS;
    }

    // Actual app
    auto ctx = p6::Context{{.title = "Simple-p6-Setup"}};
    ctx.maximize_window();

    size_t nbSquare = 50;

    float size = 0.05f;

    glm::vec2 squareSize = {1.7, 0.8};

    std::vector<Boid> boids = boidsVec(nbSquare, squareSize, size);

    // Const declaration
    scopes    scopes;
    strengths strengths;

    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Blue);

        // Dear ImGUI
        ctx.imgui = [&]() {
            ImGui::Begin("Boids");
            ImGui::SliderFloat("Scope", &scopes.scope, 0.f, 1.f);
            ImGui::SliderFloat("Separation strength", &strengths.separationStrength, 0.f, 0.1);
            ImGui::SliderFloat("Alignement strength", &strengths.alignementStrength, 0.f, 0.1);
            ImGui::SliderFloat("Cohesion strength", &strengths.cohesionStrength, 0.f, 0.1);

            ImGui::End();
        };

        // containeur (big square in the middle)
        ctx.rectangle(p6::Center{0, 0}, p6::Radii{squareSize.x, squareSize.y});

        for (size_t i = 0; i < nbSquare; i++)
        {
            glm::vec2 centerPoint = boids.at(i).getPosition();

            ctx.square(p6::Center(centerPoint), p6::Radius{size});

            boids.at(i).separationForce(boids, scopes.scope, strengths.separationStrength);
            boids.at(i).alignementForce(boids, scopes.scope, strengths.alignementStrength);
            boids.at(i).cohesionForce(boids, scopes.scope, strengths.cohesionStrength);

            boids.at(i).move();
            boids.at(i).inSquare(squareSize, size, strengths.boundsStrength, scopes.wallScope);
        }
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}