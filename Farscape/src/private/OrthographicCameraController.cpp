#include "fspch.h"
#include "Controllers/OrthographicCameraController.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Core/Input.h"
#include "Core/Codes.h"

namespace Farscape {

    OrthographicCameraController::OrthographicCameraController(float aspectRatio, float hasRotation)
        : m_AspectRatio(aspectRatio)
        , m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
        , m_HasRotation(hasRotation)
    {

    }

    void OrthographicCameraController::OnUpdate(Timestep deltaTime)
    {
        if (Input::IsKeyPressed(FS_KEY_A))               // Pressed A
        {
            m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraMoveSpeed * deltaTime;
            m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraMoveSpeed * deltaTime;
        }
        else if (Input::IsKeyPressed(FS_KEY_D))          // Pressed A
        {
            m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraMoveSpeed * deltaTime;
            m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraMoveSpeed * deltaTime;
        }

        if (Input::IsKeyPressed(FS_KEY_W))               // Pressed W
        {
            m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraMoveSpeed * deltaTime;
            m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraMoveSpeed * deltaTime;
        }
        else if (Input::IsKeyPressed(FS_KEY_S))          // Pressed S
        {
            m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraMoveSpeed * deltaTime;
            m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraMoveSpeed * deltaTime;
        }

        // Do rotation
        //if (m_HasRotation)
        {
            if (Input::IsKeyPressed(FS_KEY_Q))
                m_CameraRotation += m_CameraRotationSpeed * deltaTime;
            if (Input::IsKeyPressed(FS_KEY_E))
                m_CameraRotation -= m_CameraRotationSpeed * deltaTime;

            
            // Prevent getting huge values when constantly rotating by essentially modding them
            if (m_CameraRotation > 180.0f)
                m_CameraRotation -= 360.0f;
            else if (m_CameraRotation <= -180.0f)
                m_CameraRotation += 360.0f;
            
            m_Camera.SetRotation(m_CameraRotation);
        }

        m_Camera.SetPosition(m_CameraPosition);
        m_CameraMoveSpeed = m_ZoomLevel;
    }

    void OrthographicCameraController::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        // TODO: parametrize this constant!!! 0.25
        m_ZoomLevel -= e.GetYoffset() * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
    {
        m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

}