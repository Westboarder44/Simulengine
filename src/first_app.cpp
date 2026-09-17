#include "first_app.hpp"

namespace se {
  void FirstApp::run() {
    while(!seWindow.shouldClose()){
      glfwPollEvents();
    }

  }
} // namespace se