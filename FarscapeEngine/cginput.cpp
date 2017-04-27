#include "cginput.hpp"

#include "cgcamera.hpp"
#include "cgdisplay.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


CGCore::Input::Input(DisplayManager* currentDisplay, Camera* currentCam)
{
    m_display = currentDisplay;
    m_camera = currentCam;
    m_isAttached = true;
}

std::string CGCore::Input::ToString() const
{
    std::string x = "ddd";
    return x;
}

void CGCore::Input::Move()
{
    int state = glfwGetKey(m_display->GetWindow(), GLFW_KEY_W);
    if (state == GLFW_PRESS)
    {
        // Up key pressed
        m_camera->MoveIn();
    }

    state = glfwGetKey(m_display->GetWindow(), GLFW_KEY_S);
    if (state == GLFW_PRESS)
    {
        // Up key pressed
        m_camera->MoveBack();
    }

    state = glfwGetKey(m_display->GetWindow(), GLFW_KEY_A);
    if (state == GLFW_PRESS)
    {
        // Up key pressed
        m_camera->MoveLeft(); 
    }

    state = glfwGetKey(m_display->GetWindow(), GLFW_KEY_D);
    if (state == GLFW_PRESS)
    {
        // Up key pressed
        m_camera->MoveRight();
    }
}
