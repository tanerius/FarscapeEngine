#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Scene.h"
#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <memory>

struct Vertex;
class RenderObject;

struct ObjectBuffers {
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    uint32_t indexCount;
};

class Renderer {
public:
    Renderer();
    ~Renderer();
    
    void initialize(VkDevice device, VkPhysicalDevice physicalDevice, VkCommandPool commandPool, 
                   VkQueue graphicsQueue, VkDescriptorSetLayout descriptorSetLayout,
                   VkPipelineLayout pipelineLayout, VkPipeline graphicsPipeline);
    
    void cleanup();
    
    void updateScene(Scene* scene);
    void render(VkCommandBuffer commandBuffer, uint32_t currentFrame, 
                const std::vector<VkDescriptorSet>& descriptorSets,
                VkPipelineLayout pipelineLayout, VkPipeline graphicsPipeline,
                VkExtent2D swapChainExtent);
    
    void setCamera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up);
    void updateCamera(uint32_t currentImage, void* uniformBufferMapped, VkExtent2D swapChainExtent, float aspectRatio);

private:
    VkDevice device = VK_NULL_HANDLE;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkCommandPool commandPool = VK_NULL_HANDLE;
    VkQueue graphicsQueue = VK_NULL_HANDLE;
    
    Scene* currentScene = nullptr;
    std::map<RenderObject*, ObjectBuffers> objectBuffers;
    
    glm::vec3 cameraPosition = glm::vec3(2.0f, 2.0f, 2.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    
    void createBuffersForObject(RenderObject* object);
    void cleanupObjectBuffers(RenderObject* object);
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, 
                     VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
};
