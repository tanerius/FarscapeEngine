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
    GLfloat cameraSpeed = 5.0f * m_display->GetDeltaTime();
    if(m_keysPressed[GLFW_KEY_ESCAPE]) glfwSetWindowShouldClose(m_display->GetWindow(), GL_TRUE);
    if(m_keysPressed[GLFW_KEY_W]) m_camera->MoveIn();
    if(m_keysPressed[GLFW_KEY_S]) m_camera->MoveBack();
    if(m_keysPressed[GLFW_KEY_A]) m_camera->MoveLeft();
    if(m_keysPressed[GLFW_KEY_D]) m_camera->MoveRight();

    // TODO: roll, pitch, yaw
}
