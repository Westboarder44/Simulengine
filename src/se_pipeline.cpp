#include "se_pipeline.hpp"

#include <fstream>
#include <stdexcept>
#include <spdlog/spdlog.h>
#include <filesystem>

namespace se {

  SePipeline::SePipeline(SeDevice &device, const std::string &vertFilepath, const std::string &fragFilepath, const PipelineConfigInfo &configInfo) : seDevice{device}{
    createGraphicsPipeline(vertFilepath, fragFilepath, configInfo);
  }

  std::vector<char> SePipeline::readFile(const std::string &filepath) {
    std::ifstream file{filepath, std::ios::ate | std::ios::binary};
    if (!file.is_open()) {
      spdlog::info("Current working dir: {}", std::filesystem::current_path().string());
      spdlog::info("Attempting to open: {}", std::filesystem::absolute(filepath).string());
      spdlog::error("Failed to open file: {}", filepath);
      throw std::runtime_error("failed to open file: " + filepath);
    }

    size_t fileSize = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();
    return buffer;
  }

  void SePipeline::createGraphicsPipeline(const std::string &vertFilepath, const std::string &fragFilepath, const PipelineConfigInfo &configInfo) {
    auto vertCode = readFile(vertFilepath);
    auto fragCode = readFile(fragFilepath);

    spdlog::info("Vertex shader code size: " + std::to_string(vertCode.size()));
    spdlog::info("Fragment shader code size: " + std::to_string(fragCode.size()));
  }

  void SePipeline::createShaderModule(const std::vector<char> &code, VkShaderModule *shaderModule) {
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t *>(code.data());

    if (vkCreateShaderModule(seDevice.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS) {
      spdlog::error("Failed to create shader module");
      throw std::runtime_error("failed to create shader module!");
    }
  }

  PipelineConfigInfo SePipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height) {
    PipelineConfigInfo configInfo{};

    return configInfo;
  }
}