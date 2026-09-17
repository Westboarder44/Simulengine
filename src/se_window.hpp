#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace se {
    class SeWindow {
      public:

        SeWindow(int w, int h, std::string name);
        ~SeWindow();

        SeWindow(const SeWindow&) = delete;
        SeWindow& operator=(const SeWindow&) = delete;

        bool shouldClose() { return glfwWindowShouldClose(window); }

        void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

      private: 
        void initWindow();

        const int width;
        const int height;

        std::string windowName;
        GLFWwindow *window;
  };
} // namespace se