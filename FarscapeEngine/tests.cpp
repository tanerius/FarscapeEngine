#include "cgdisplay.hpp"
#include "cgtransform.hpp"
#include "cgcamera.hpp"
#include "cgmesh.hpp"

#ifdef WINDOWS
static const char* TEXTURE_FILE = "C:\\Users\\taner\\Documents\\Dev\\FarscapeEngine\\FarscapeEngine\\assets\\tex512.png";
#else
static const char* TEXTURE_FILE = "/Users/tanerselim/Dev/FarscapeEngine/FarscapeEngine/assets/tex512.png";
#endif

int main()
{
    
    
    printf("Hello\n");
    
    CGCore::DisplayManager* Display = new CGCore::DisplayManager();
    Display->CreateDisplay();
    Display->GetInfo();
    
    
    int w,h;
    Display->GetResolution(w, h);
    float aspectRatio = (float)w / (float)h;
    CGCore::Camera* MainCamera = new CGCore::Camera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, aspectRatio, 0.1f, 100.0f);
    printf("The camera: \n%s", MainCamera->ToString().c_str());
    
    return 0;
    /*
    // Initialize the display
    
    
    // DEPRICATED CGCore::Camera* MainCamera = new CGCore::Camera(Display);
    // Call a renderer to set states and create a projection matrix
    

    bool HasError = false;


    // Start main loop
    while(!Display->CloseRequested() && (!HasError))
    {

        Display->UpdateDisplay();
    }

    Display->DestroyDisplay();
    delete Display;

    return 0;
     */
}
