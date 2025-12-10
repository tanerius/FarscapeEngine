#include "RenderObject.h"
#include "VulkanApp.h"

RenderObject::RenderObject(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices)
    : vertices(vertices), indices(indices) {
}

glm::mat4 RenderObject::getModelMatrix() const {
    glm::mat4 model = glm::mat4(1.0f);
    
    // Apply transformations: translate -> rotate -> scale
    model = glm::translate(model, position);
    model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);
    
    return model;
}
