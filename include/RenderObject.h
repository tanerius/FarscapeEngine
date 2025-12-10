#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <cstdint>

struct Vertex;

class RenderObject {
public:
    RenderObject(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices);
    
    const std::vector<Vertex>& getVertices() const { return vertices; }
    const std::vector<uint16_t>& getIndices() const { return indices; }
    
    void setPosition(const glm::vec3& pos) { position = pos; }
    void setRotation(const glm::vec3& rot) { rotation = rot; }
    void setScale(const glm::vec3& scl) { scale = scl; }
    
    glm::vec3 getPosition() const { return position; }
    glm::vec3 getRotation() const { return rotation; }
    glm::vec3 getScale() const { return scale; }
    
    glm::mat4 getModelMatrix() const;

private:
    std::vector<Vertex> vertices;
    std::vector<uint16_t> indices;
    
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
};
