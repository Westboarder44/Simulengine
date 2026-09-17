#include "se_window.hpp"
#include "spdlog/spdlog.h"

#include <stdexcept>

namespace se {
  SeWindow::SeWindow(int w, int h, std::string name) : width{w}, height{h}, windowName{name} {
    initWindow();
  }

  SeWindow ::~SeWindow() {
    glfwDestroyWindow(window);
    glfwTerminate();
  }

  void SeWindow::initWindow() {
    if (!glfwInit()) {
      spdlog::error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
    if (!window) {
      spdlog::error("Failed to create GLFW window");
    }
  }

  void SeWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface) {
    if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
      spdlog::error("Failed to create window surface");
      throw std::runtime_error("Failed to create window surface");
    }
  }
} // namespace se