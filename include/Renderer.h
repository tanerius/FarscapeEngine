#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Scene.h"
#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <memory>
#include <array>

struct Vertex;
class RenderObject;

struct ObjectBuffers
{
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    uint32_t indexCount;
};

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void initialize(VkDevice device, VkPhysicalDevice physicalDevice, VkCommandPool commandPool,
                    VkQueue graphicsQueue);

    void initializeImGui(GLFWwindow *window, VkInstance instance, VkRenderPass renderPass,
                         VkQueue graphicsQueue, uint32_t imageCount);

    void createOffscreenRenderPass(VkFormat colorFormat, VkFormat depthFormat);
    void createOffscreenResources(VkFormat colorFormat, VkFormat depthFormat);
    VkRenderPass getOffscreenRenderPass() const { return offscreenRenderPass; }
    void renderSceneToTexture(VkCommandBuffer commandBuffer, uint32_t currentFrame,
                              const std::vector<VkDescriptorSet> &descriptorSets,
                              VkPipelineLayout pipelineLayout, VkPipeline graphicsPipeline);

    void cleanup();
    void updateScene(Scene *scene);

    void setCamera(const glm::vec3 &position, const glm::vec3 &target, const glm::vec3 &up);
    void updateCamera(uint32_t currentImage, void *uniformBufferMapped, VkExtent2D swapChainExtent, float aspectRatio);

    void renderImGui(VkCommandBuffer commandBuffer);
    void newImGuiFrame();

    std::array<float, 3> &getClearColor() { return clearColor; }

private:
    VkDevice device = VK_NULL_HANDLE;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkCommandPool commandPool = VK_NULL_HANDLE;
    VkQueue graphicsQueue = VK_NULL_HANDLE;

    Scene *currentScene = nullptr;
    std::map<RenderObject *, ObjectBuffers> objectBuffers;

    glm::vec3 cameraPosition = glm::vec3(2.0f, 2.0f, 2.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    // ImGui
    VkDescriptorPool imguiDescriptorPool = VK_NULL_HANDLE;
    std::array<float, 3> clearColor = {0.0f, 0.0f, 0.0f};

    // Offscreen rendering for 3D viewport
    VkImage offscreenImage = VK_NULL_HANDLE;
    VkDeviceMemory offscreenImageMemory = VK_NULL_HANDLE;
    VkImageView offscreenImageView = VK_NULL_HANDLE;
    VkFramebuffer offscreenFramebuffer = VK_NULL_HANDLE;
    VkSampler offscreenSampler = VK_NULL_HANDLE;
    VkDescriptorSet offscreenDescriptorSet = VK_NULL_HANDLE;
    VkImage offscreenDepthImage = VK_NULL_HANDLE;
    VkDeviceMemory offscreenDepthImageMemory = VK_NULL_HANDLE;
    VkImageView offscreenDepthImageView = VK_NULL_HANDLE;
    uint32_t offscreenWidth = 1280;
    uint32_t offscreenHeight = 720;
    VkRenderPass offscreenRenderPass = VK_NULL_HANDLE;

    void createBuffersForObject(RenderObject *object);
    void cleanupObjectBuffers(RenderObject *object);
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
                      VkBuffer &buffer, VkDeviceMemory &bufferMemory);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    void cleanupOffscreenResources();
    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling,
                     VkImageUsageFlags usage, VkMemoryPropertyFlags properties,
                     VkImage &image, VkDeviceMemory &imageMemory);
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
};
