//
//  farscape.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 9/19/17.
//  Copyright © 2017 Taner Selim. All rights reserved.
//

#ifndef farscape_hpp
#define farscape_hpp
#include <string>

namespace CGCore
{
    
    // The singleton class through which everything should occur
    class FarscapeEngine
    {
    private:
        /* Here will be the instance stored. */
        static FarscapeEngine* instance;
        bool isInitialized = false;
        short HorizontalResolution;
        short VerticalResolution;
        bool UsingMouse;
        std::string AppName;
        short MinFPS;
        bool DebugMode;
        
        /* Private constructor to prevent instancing. */
        FarscapeEngine();
        
    public:
        /* Static access method. */
        static FarscapeEngine* getInstance();
        // Use this to initialize the engine
        void Init(
            const char* _AppName,
            const short _HorizRes,
            const short _VertRes,
            const short _MaxFPS,
            const bool _UsingMouse,
            bool _dbg = true
        );
    };
}




#endif /* farscape_hpp */
