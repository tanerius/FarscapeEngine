//
//  Main.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/25/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#include "Engine/Application.h"

bool test = false;

int main()
{
    Farscape::Application app("Minecraft");
    if (test)
    {
        app.Test();
    }
    else{
        app.Start();
    }
    
    return 0;
}


