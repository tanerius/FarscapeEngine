#pragma once
#pragma warning(disable:4201)
#include <glm/glm.hpp>
#pragma warning(default:4201)
namespace Farscape {
    /**
     * Implementation of a AABB bounding box
     *
     * Box where the faces are aligned to the axes of the coordinate space.
     * An AABB is defined by the positions of the Minimum and the Maximum box corner.
     * Minimum must be less than Maximum. But this rule is not enforced;
     * no exceptions are thrown in the setter of the properties.
     */
    struct AABB
    {
        glm::vec3 Min;
        glm::vec3 Max;

        AABB()
            : Min(0.0f)
            , Max(0.0f)
        { }


        AABB(const glm::vec3& min, const glm::vec3& max)
            : Min(min)
            , Max(max)
        { }

    };


}