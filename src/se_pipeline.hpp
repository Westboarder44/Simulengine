#pragma once

#include "se_device.hpp"

// std
#include <string>
#include <vector>

namespace se {
  struct PipelineConfigInfo {

  };
  class SePipeline {
    public:
      SePipeline(SeDevice &device, const std::string &vertFilepath, const std::string &fragFilepath, const PipelineConfigInfo &configInfo);

      ~SePipeline() {};

      SePipeline(const SePipeline &) = delete;
      void operator=(const SePipeline&) = delete;

      static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

    private:
      static std::vector<char> readFile(const std::string &filepath);

      void createGraphicsPipeline(const std::string &vertFilepath, const std::string &fragFilepath, const PipelineConfigInfo &configinfo);

      void createShaderModule(const std::vector<char> &code, VkShaderModule *shaderModule);

      SeDevice &seDevice;
      VkPipeline graphicsPipeline;
      VkShaderModule vertShaderModule;
      VkShaderModule fragShaderModule;
  };

}