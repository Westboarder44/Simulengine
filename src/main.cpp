#include <iostream>
#define VOLK_IMPLEMENTATION
#include <volk.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

int main() {
    spdlog::info("Simulengine: Third-party integration test.");

    if (!glfwInit()) {
        spdlog::error("Failed to initialize GLFW");
        return -1;
    }

    if (volkInitialize() != VK_SUCCESS) {
        spdlog::error("Failed to initialize Volk");
        return -1;
    }

    spdlog::info("Libraries initialized successfully.");
    
    glfwTerminate();
    return 0;
}