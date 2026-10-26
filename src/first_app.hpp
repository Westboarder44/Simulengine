#pragma once 
#include "se_window.hpp"
#include "se_pipeline.hpp"
#include "se_device.hpp"
#include "se_swap_chain.hpp"

//std
#include <memory>
#include <vector>

namespace se {
  class FirstApp {
    public:
      static constexpr int WIDTH = 800;
      static constexpr int HEIGHT = 600;

      FirstApp();
      ~FirstApp();

      FirstApp(const FirstApp &) = delete;
      FirstApp &operator=(const FirstApp &) = delete;

      void run();
      SeWindow* getSeWindow() { return &seWindow; }
    private:
      void createPipelineLayout();
      void createPipeline();
      void createCommandBuffers();
      void drawFrame();

      SeWindow seWindow{WIDTH, HEIGHT, "Hello Vulkan!"};
      SeDevice seDevice{seWindow};
      SeSwapchain seSwapchain{seDevice, seWindow.getExtent()};
      std::unique_ptr<SePipeline> sePipeline;
      VkPipelineLayout pipelineLayout;
      std::vector<VkCommandBuffer> commandBuffers;

  };
}