#include "cginput.hpp"

#include "cgcamera.hpp"
#include "cgdisplay.hpp"
#ifdef WINDOWS
#include<windows.h>
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>


CGCore::Input::Input(DisplayManager* currentDisplay, Camera* currentCam)
{
    m_display = currentDisplay;
    m_camera = currentCam;
    m_isAttached = true;
    m_keysPressed = currentDisplay->GetHandledKeys();
}

std::string CGCore::Input::ToString() const
{
    std::string x = "ddd";
    return x;
}

void CGCore::Input::Move()
{
    GLfloat cameraSpeed = 1.5f * m_display->GetDeltaTime();
    GLfloat rotationAngleStep = 1.0f;
    if(m_keysPressed[GLFW_KEY_ESCAPE]) glfwSetWindowShouldClose(m_display->GetWindow(), GL_TRUE);
    if(m_keysPressed[GLFW_KEY_W]) m_camera->MoveIn(cameraSpeed);
    if(m_keysPressed[GLFW_KEY_S]) m_camera->MoveBack(cameraSpeed);
    if(m_keysPressed[GLFW_KEY_A]) m_camera->MoveLeft(cameraSpeed);
    if(m_keysPressed[GLFW_KEY_D]) m_camera->MoveRight(cameraSpeed);

    if(m_keysPressed[GLFW_KEY_Q])
    {
        m_camera->Yaw(-rotationAngleStep);
    }
    if(m_keysPressed[GLFW_KEY_E])
    {
        m_camera->Yaw(rotationAngleStep);
    }

    // Zoom
    if(m_keysPressed[GLFW_KEY_R]) m_camera->Zoom(-0.05f);
    if(m_keysPressed[GLFW_KEY_F]) m_camera->Zoom(0.05f);
    
    double offset = m_display->GetMouseOffsetY();
    if((offset > 0.0001) || (offset < -0.0001))
    {
        m_camera->Pitch(offset);
    }
    
    offset = m_display->GetMouseOffsetX();
    if((offset > 0.0001) || (offset < -0.0001))
    {
        m_camera->Yaw(offset);
    }
    


    // TODO: roll, pitch, yaw
}
