#pragma once 
#include "se_window.hpp"
#include "se_pipeline.hpp"
#include "se_device.hpp"

namespace se {
  class FirstApp {
    public:
      static constexpr int WIDTH = 800;
      static constexpr int HEIGHT = 600;
      void run();
      SeWindow* getSeWindow() { return &seWindow; }
    private:
      SeWindow seWindow{WIDTH, HEIGHT, "Hello Vulkan!"};
      SeDevice seDevice{seWindow};
      SePipeline sePipeline{seDevice, "../src/shaders/simple_shader.vert.spv", "../src/shaders/simple_shader.frag.spv", SePipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
  };
}