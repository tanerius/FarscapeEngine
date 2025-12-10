#include "Renderer.h"
#include "VulkanApp.h"
#include "RenderObject.h"
#include <stdexcept>
#include <glm/gtc/matrix_transform.hpp>
#include <cstring>

Renderer::Renderer() {
}

Renderer::~Renderer() {
    cleanup();
}

void Renderer::initialize(VkDevice device, VkPhysicalDevice physicalDevice, VkCommandPool commandPool,
                         VkQueue graphicsQueue, VkDescriptorSetLayout descriptorSetLayout,
                         VkPipelineLayout pipelineLayout, VkPipeline graphicsPipeline) {
    this->device = device;
    this->physicalDevice = physicalDevice;
    this->commandPool = commandPool;
    this->graphicsQueue = graphicsQueue;
}

void Renderer::cleanup() {
    for (auto& pair : objectBuffers) {
        cleanupObjectBuffers(pair.first);
    }
    objectBuffers.clear();
}

void Renderer::updateScene(Scene* scene) {
    if (currentScene != scene) {
        // Clean up old scene buffers
        for (auto& pair : objectBuffers) {
            cleanupObjectBuffers(pair.first);
        }
        objectBuffers.clear();
        
        currentScene = scene;
        
        // Create buffers for new scene objects
        if (currentScene) {
            for (const auto& obj : currentScene->getObjects()) {
                createBuffersForObject(obj.get());
            }
        }
    } else if (currentScene) {
        // Check for new objects and create buffers
        for (const auto& obj : currentScene->getObjects()) {
            if (objectBuffers.find(obj.get()) == objectBuffers.end()) {
                createBuffersForObject(obj.get());
            }
        }
    }
}

void Renderer::render(VkCommandBuffer commandBuffer, uint32_t currentFrame,
                     const std::vector<VkDescriptorSet>& descriptorSets,
                     VkPipelineLayout pipelineLayout, VkPipeline graphicsPipeline,
                     VkExtent2D swapChainExtent) {
    if (!currentScene) return;
    
    // Set dynamic viewport and scissor
    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(swapChainExtent.width);
    viewport.height = static_cast<float>(swapChainExtent.height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

    VkRect2D scissor{};
    scissor.offset = {0, 0};
    scissor.extent = swapChainExtent;
    vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
    
    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 
                           0, 1, &descriptorSets[currentFrame], 0, nullptr);
    
    // Render each object in the scene
    for (const auto& obj : currentScene->getObjects()) {
        auto it = objectBuffers.find(obj.get());
        if (it == objectBuffers.end()) continue;
        
        const ObjectBuffers& buffers = it->second;
        
        VkBuffer vertexBuffers[] = {buffers.vertexBuffer};
        VkDeviceSize offsets[] = {0};
        vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
        vkCmdBindIndexBuffer(commandBuffer, buffers.indexBuffer, 0, VK_INDEX_TYPE_UINT16);
        
        vkCmdDrawIndexed(commandBuffer, buffers.indexCount, 1, 0, 0, 0);
    }
}

void Renderer::setCamera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up) {
    cameraPosition = position;
    cameraTarget = target;
    cameraUp = up;
}

void Renderer::updateCamera(uint32_t currentImage, void* uniformBufferMapped, 
                           VkExtent2D swapChainExtent, float aspectRatio) {
    UniformBufferObject ubo{};
    
    // Use the first object's model matrix if available
    if (currentScene && currentScene->getObjectCount() > 0) {
        ubo.model = currentScene->getObjects()[0]->getModelMatrix();
    } else {
        ubo.model = glm::mat4(1.0f);
    }
    
    // Camera view matrix
    ubo.view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);
    
    // Projection matrix
    ubo.proj = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 10.0f);
    ubo.proj[1][1] *= -1; // Flip Y for Vulkan
    
    memcpy(uniformBufferMapped, &ubo, sizeof(ubo));
}

void Renderer::createBuffersForObject(RenderObject* object) {
    const auto& vertices = object->getVertices();
    const auto& indices = object->getIndices();
    
    ObjectBuffers buffers{};
    
    // Create vertex buffer
    VkDeviceSize vertexBufferSize = sizeof(vertices[0]) * vertices.size();
    
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    createBuffer(vertexBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                stagingBuffer, stagingBufferMemory);
    
    void* data;
    vkMapMemory(device, stagingBufferMemory, 0, vertexBufferSize, 0, &data);
    memcpy(data, vertices.data(), (size_t)vertexBufferSize);
    vkUnmapMemory(device, stagingBufferMemory);
    
    createBuffer(vertexBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, buffers.vertexBuffer, buffers.vertexBufferMemory);
    
    copyBuffer(stagingBuffer, buffers.vertexBuffer, vertexBufferSize);
    
    vkDestroyBuffer(device, stagingBuffer, nullptr);
    vkFreeMemory(device, stagingBufferMemory, nullptr);
    
    // Create index buffer
    VkDeviceSize indexBufferSize = sizeof(indices[0]) * indices.size();
    
    createBuffer(indexBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                stagingBuffer, stagingBufferMemory);
    
    vkMapMemory(device, stagingBufferMemory, 0, indexBufferSize, 0, &data);
    memcpy(data, indices.data(), (size_t)indexBufferSize);
    vkUnmapMemory(device, stagingBufferMemory);
    
    createBuffer(indexBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, buffers.indexBuffer, buffers.indexBufferMemory);
    
    copyBuffer(stagingBuffer, buffers.indexBuffer, indexBufferSize);
    
    vkDestroyBuffer(device, stagingBuffer, nullptr);
    vkFreeMemory(device, stagingBufferMemory, nullptr);
    
    buffers.indexCount = static_cast<uint32_t>(indices.size());
    
    objectBuffers[object] = buffers;
}

void Renderer::cleanupObjectBuffers(RenderObject* object) {
    auto it = objectBuffers.find(object);
    if (it != objectBuffers.end()) {
        vkDestroyBuffer(device, it->second.vertexBuffer, nullptr);
        vkFreeMemory(device, it->second.vertexBufferMemory, nullptr);
        vkDestroyBuffer(device, it->second.indexBuffer, nullptr);
        vkFreeMemory(device, it->second.indexBufferMemory, nullptr);
        objectBuffers.erase(it);
    }
}

void Renderer::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
                            VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("Failed to allocate buffer memory!");
    }

    vkBindBufferMemory(device, buffer, bufferMemory, 0);
}

void Renderer::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = commandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    VkBufferCopy copyRegion{};
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(graphicsQueue);

    vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
}

uint32_t Renderer::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("Failed to find suitable memory type!");
}
