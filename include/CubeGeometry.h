#pragma once

#include <vector>
#include <cstdint>
#include <glm/glm.hpp>

struct Vertex;

class CubeGeometry {
public:
    static std::vector<Vertex> getVertices();
    static std::vector<uint16_t> getIndices();
};
