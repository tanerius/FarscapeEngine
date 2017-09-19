//
//  farscape.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 9/19/17.
//  Copyright © 2017 Taner Selim. All rights reserved.
//

#include "farscape.hpp"
#include "cgobj.hpp"
#include "cgdisplay.hpp"
#include "cgtransform.hpp"
#include "cgcamera.hpp"
#include "cgmesh.hpp"
#include "cgshader.hpp"
#include "cgtexture.hpp"
#include "cgrenderer.hpp"
#include "cgentity.hpp"
#include <vector>
#include <ctime>
#include "cginput.hpp"
#include "cgcore.hpp"



    
/* Null, because instance will be initialized on demand. */
CGCore::FarscapeEngine* CGCore::FarscapeEngine::instance = nullptr;

CGCore::FarscapeEngine* CGCore::FarscapeEngine::getInstance()
{
    if ((instance == 0) || (instance == nullptr))
    {
        instance = new CGCore::FarscapeEngine();
    }
    
    return instance;
}

CGCore::FarscapeEngine::FarscapeEngine()
{
    // Initialize a high precision timer
    CGCore::InitHighPrecisionTimers();
    
    // Create the display manager instance
    CGCore::DisplayManager::getInstance();
}
    

