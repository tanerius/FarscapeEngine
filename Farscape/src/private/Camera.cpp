#include "fspch.h"
#include "Renderer/Camera.h"

#include <glm/gtc/matrix_transform.hpp>


namespace Farscape {



    OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom)
        : m_ProjectionMatrix(glm::ortho(left, right, top, bottom, -1.0f, 1.0f))
        , m_ViewMatrix(1.0f)
    {
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::SetPosition(const glm::vec3 & position)
    {
        m_Position = position;
        UpdateViewMatrix();
    }

    void OrthographicCamera::SetRotation(const float rotation)
    {
        m_Rotation = rotation;
        UpdateViewMatrix();
    }

    const glm::mat4 & OrthographicCamera::GetMatrix(EMatrixType type) const
    {
        // TODO: insert return statement here
        switch (type)
        {
            case EMatrixType::E_Projection: return m_ProjectionMatrix;
            case EMatrixType::E_View: return m_ViewMatrix;
            case EMatrixType::E_ViewProjection: return m_ViewProjectionMatrix;
        }
        FS_CORE_ASSERT(false, "GetMatrix incorrrect matrix type specified. Returning projection matrix!");
        return m_ProjectionMatrix;
    }

    void OrthographicCamera::UpdateViewMatrix()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * 
            glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

        m_ViewMatrix = glm::inverse(transform);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

}
