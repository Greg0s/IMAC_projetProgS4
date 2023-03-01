#include "p6/p6.h"
#include <cstdlib>
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

int main(int argc, char *argv[]) {
  { // Run the tests
    if (doctest::Context{}.run() != 0)
      return EXIT_FAILURE;
    // The CI does not have a GPU so it cannot run the rest of the code.
    const bool no_gpu_available =
        argc >= 2 &&
        strcmp(argv[1], "-nogpu") ==
            0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    if (no_gpu_available)
      return EXIT_SUCCESS;
  }

  // Actual app
  auto ctx = p6::Context{{.title = "Simple-p6-Setup"}};
  ctx.maximize_window();

  size_t nbSquare = 1;

  std::vector<glm::vec2> points;
  std::vector<glm::vec2> directions;
  for (size_t i = 0; i < nbSquare; i++) {
    points.push_back(p6::random::point(ctx));
    directions.push_back(p6::random::direction());
  }

  // Declare your infinite update loop.
  ctx.update = [&]() {
    ctx.background(p6::NamedColor::Blue);

    ctx.square(p6::Center{0, 0}, p6::Radius{1.f});

    for (size_t i = 0; i < nbSquare; i++) {
      ctx.square(p6::Center{points[i]}, p6::Radius{0.1f});
      points[i] += p6::random::direction() * 0.02f;
    }
  };

  // Should be done last. It starts the infinite loop.
  ctx.start();
}