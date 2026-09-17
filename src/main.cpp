#include "first_app.hpp"

// std
#include <cstdlib>
#include <stdexcept>

// logging
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

int main() {
  se::FirstApp app{};
  if(!(app.getSeWindow() -> shouldClose())) {
    spdlog::set_level(spdlog::level::info);
    spdlog::info("Starting application");
    spdlog::info("Size of window is " + std::to_string(app.WIDTH) + "x" + std::to_string(app.HEIGHT));
    try {
      app.run();
    } catch (const std::exception& e) {
      spdlog::error(e.what());
      return EXIT_FAILURE;
    }
  }
  spdlog::info("Application finished successfully");
  return EXIT_SUCCESS;
}