#include <cstdlib>
#include "p6/p6.h"
// #include <sys/_types/_size_t.h>
#define DOCTEST_CONFIG_IMPLEMENT
#include "Boid.hpp"
#include "doctest/doctest.h"

void print(float val)
{
    std::cout << val << std::endl;
}

void print(glm::vec2 val)
{
    std::cout << "x: " << val.x << "y: " << val.y << std::endl;
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

    size_t    nbSquare = 15;
    glm::vec2 speed    = {0.005, 0.005};

    float size = 0.1f;

    float squareSize = 1;

    glm::vec2 pos;
    glm::vec2 direction;

    std::vector<Boid> boids;

    // création du vector des boids
    for (size_t i = 0; i < nbSquare; i++)
    {
        // square appears only in the square = center of the square
        pos = p6::random::point(
            {
                -squareSize + size,
                -squareSize + size,
            },
            {
                squareSize - size,
                squareSize - size,
            }
        );
        std::cout << "pos : " << pos.x << " " << pos.y << std::endl;
        // squares have a random direction
        direction = p6::random::direction();
        // create the boid of the square i
        Boid boid = Boid(pos, direction, speed);
        // add this boid to the others
        boids.push_back(boid);
    }

    // Const declaration
    float       scope              = 0.5;
    const float wallScope          = 0.1;
    const float boundsStrength     = 1;
    float       separationStrength = 0.04; // 2
    float       alignementStrength = 0.03; // 5
    float       cohesionStrength   = 0.01; // 5

    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Blue);

        // Dear ImGUI
        ctx.imgui = [&]() {
            ImGui::Begin("Boids");
            ImGui::SliderFloat("Boids scope", &scope, 0.f, 1.f);
            ImGui::SliderFloat("Separation strength", &separationStrength, 0.f, 1.f);
            ImGui::SliderFloat("Alignement strength", &alignementStrength, 0.f, 1.f);
            ImGui::SliderFloat("Cohesion strength", &cohesionStrength, 0.f, 1.f);

            ImGui::End();
        };

        // containeur (big square in the middle)
        ctx.square(p6::Center{0, 0}, p6::Radius{squareSize});

        for (size_t i = 0; i < nbSquare; i++)
        {
            glm::vec2 centerPoint = boids.at(i).getPosition();

            ctx.square(p6::Center(centerPoint), p6::Radius{size});

            boids.at(i).separationForce(boids, scope, separationStrength);
            boids.at(i).alignementForce(boids, scope, alignementStrength);
            boids.at(i).cohesionForce(boids, scope, cohesionStrength);

            boids.at(i).move();
            boids.at(i).inSquare(squareSize, size, boundsStrength, wallScope);
        }
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}