#pragma once
#include "Core/Core.h"
#include "Core/Timestep.h"
#include "Renderer/Camera.h"


namespace Farscape {
    class Event;
    class MouseScrolledEvent;
    class WindowResizeEvent;

    class OrthographicCameraController : public ICameraController
    {
    public:
        // hasRotation = true default means that this controller will have a rotatable camera by default
        OrthographicCameraController(float aspectRatio, bool hasRotation = true); // default zoom level 1.0  with 2 units space
        virtual ~OrthographicCameraController() {}

        void OnUpdate(Timestep deltaTime);
        void OnEvent(Event& e);
        OrthographicCamera& GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }

        virtual const ICamera* GetCameraInterface() override { return &GetCamera(); }

        float GetZoomLevel() const { return m_ZoomLevel; }
        void SetZoomLevel(float level) { m_ZoomLevel = level; }
    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);
    private:
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        // TODO fix this - mutable here might not be good just because of GetCamera
        OrthographicCamera m_Camera;

        bool m_HasRotation;

        glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
        float m_CameraRotation = 0.0f;
        float m_CameraMoveSpeed = 5.0f;
        float m_CameraRotationSpeed = 90.0f; // degrees per second
    };

}