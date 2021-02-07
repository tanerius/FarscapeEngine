#include "cgdisplay.hpp"
#ifdef WINDOWS
#include<windows.h>
#endif
#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include "cgcallback.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>



/* Null, because instance will be initialized on demand. */
CGCore::DisplayManager* CGCore::DisplayManager::instance = nullptr;

CGCore::DisplayManager* CGCore::DisplayManager::getInstance()
{
    if ((instance == nullptr) || (instance == 0))
    {
        instance = new CGCore::DisplayManager();
    }
    
    return instance;
}


CGCore::DisplayManager::DisplayManager()
{
}


bool CGCore::DisplayManager::CloseRequested()
{
    return glfwWindowShouldClose(GLFWWindowPtr);
}

void CGCore::DisplayManager::CreateDisplay(const bool UsingMouse, short WidthRez, short HeightRez)
{
    // Creating a display
    assert(GLFWWindowPtr == 0);
    // set the screen resolution
    DisplayWidth = WidthRez;
    DisplayHeight = HeightRez;
    
    
    // Initialize GLFW, and if it fails to initialize for any reason, print it out to STDERR.
    // Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		exit(EXIT_FAILURE);
	}

    for (int c=0; c<MAX_HANDLED_KEYS; c++)
    {
        CGCore::HandledKeys[c] = false;
    }

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Try 4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1); // try 1
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // Create a window to put our stuff in.
    GLFWWindowPtr = glfwCreateWindow(DisplayWidth, DisplayHeight, "Farscape Demo: ", NULL, NULL);

    if( GLFWWindowPtr == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(GLFWWindowPtr);

    glfwSetKeyCallback(GLFWWindowPtr, CGCore::CGCallbacks::KeyCallback); // key capture
    glfwSetErrorCallback(CGCallbacks::ErrorCallback);
    // If we  are using mouse
    if (UsingMouse)
    {
        m_UsingMouse = true;
        CGCore::FirstMouseEvent = true;
        CGCore::LastMouseX = DisplayWidth / 2;
        CGCore::LastMouseY = DisplayHeight / 2;
        CGCore::MouseSensitivity = 0.05f;
        glfwSetInputMode(GLFWWindowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(GLFWWindowPtr, CGCore::CGCallbacks::MouseCallback);
        
    }
    else{
        m_UsingMouse = false;
    }
    
    glfwWindowHint (GLFW_SAMPLES, 4);

    // Initialize GLEW
	glewExperimental = GL_TRUE; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		exit(EXIT_FAILURE);
	}
    // Ensure we can capture the escape key being pressed below
	glfwSetInputMode(GLFWWindowPtr, GLFW_STICKY_KEYS, GL_TRUE);


}

void CGCore::DisplayManager::DestroyDisplay()
{
    // Destroy the display
    glfwDestroyWindow(GLFWWindowPtr);
    glfwTerminate();
}

void CGCore::DisplayManager::GetInfo()
{
    printf("GL Information:\n");
    printf("Supported GL version: %s \n",glGetString(GL_VERSION));
    printf("Supported shading lang: %s \n",glGetString (GL_SHADING_LANGUAGE_VERSION));
    printf("Current GL vendor: %s \n",glGetString(GL_VENDOR));
    printf("Current GL renderer: %s \n",glGetString(GL_RENDERER));
    
    GLint num=0;
    GLuint i;
    glGetIntegerv(GL_NUM_EXTENSIONS, &num);
    printf("GL extensions supported: %d\n", num);
    if (num < 1) {
        return;
    }
    
    for (i=0; i<(GLuint)num; i++) {
        const GLubyte *ext=glGetStringi(GL_EXTENSIONS,i);
        if (ext) {
            printf("  %s\n",ext);
        }
    }
}


float CGCore::DisplayManager::GetRunningTime() const
{ 
     return glfwGetTime (); 
}



void CGCore::DisplayManager::ResetOffset()
{
    CGCore::MouseOffsetX = 0.0f;
    CGCore::MouseOffsetY = 0.0f;
}


void CGCore::DisplayManager::SetMouseSensitivity(const float s)
{
    CGCore::MouseSensitivity = s;
}


void CGCore::DisplayManager::UpdateDisplay()
{
    UpdateFpsCounter();
    // Swap the buffers so that what we drew will appear on the screen.
    glfwSwapBuffers(GLFWWindowPtr);
    glfwPollEvents();
}



void CGCore::DisplayManager::UpdateFpsCounter()
{
    double current_seconds;    

    current_seconds = glfwGetTime ();
    delta_time = current_seconds - previous_seconds;
    if (delta_time > 0.25) {
        double fps;
        char tmp[256];
        
        previous_seconds = current_seconds;
        fps = (double)frame_count / delta_time;
        sprintf (tmp, "Farscape demo - opengl @ fps: %.2f", fps);
        glfwSetWindowTitle (GLFWWindowPtr, tmp);
        frame_count = 0;
    }
    frame_count++;
}

void CGCore::DisplayManager::WriteDisplay(const char* Msg)
{
    printf("Log: %s", Msg);
}