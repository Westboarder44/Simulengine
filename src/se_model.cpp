#include "se_model.hpp"

// std
#include<cassert>
#include<cstring>

namespace se {
  SeModel::SeModel(SeDevice &device, const std::vector<Vertex> &vertices) : seDevice{device} {
    createVertexBuffers(vertices);
  }

  SeModel::~SeModel() {
    vkDestroyBuffer(seDevice.device(), vertexBuffer, nullptr);
    vkFreeMemory(seDevice.device(), vertexBufferMemory, nullptr);
  }

  void SeModel::createVertexBuffers(const std::vector<Vertex> &vertices) {
    vertexCount = static_cast<uint32_t>(vertices.size());
    assert(vertexCount >= 3 && "Vertex count must be at least 3");
    VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount;

    seDevice.createBuffer(bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, vertexBuffer, vertexBufferMemory);
    void *data;
    vkMapMemory(seDevice.device(), vertexBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
    vkUnmapMemory(seDevice.device(), vertexBufferMemory);
  }

  void SeModel::draw(VkCommandBuffer commandBuffer) {
    vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
  }

  void SeModel::bind(VkCommandBuffer commandBuffer) {
    VkBuffer buffers[] = {vertexBuffer};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
  }

  std::vector<VkVertexInputBindingDescription> SeModel::Vertex::getBindingDescriptions() {
    return {{0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX}};
  }

  std::vector<VkVertexInputAttributeDescription> SeModel::Vertex::getAttributeDescriptions() {
    return {{0, 0, VK_FORMAT_R32G32_SFLOAT, 0}};
  }

} // namespace se