//
//  SingletonBase.h
//  FarscapeEngine
//
//  Created by Taner Selim on 1/25/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef SingletonBase_h
#define SingletonBase_h

//
//  FSSingletonBase.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/25/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef FSSingletonBase_h
#define FSSingletonBase_h
#include  <utility>

namespace Farscape
{
    // The singleton class through which everything should occur
    template <typename T>
    class SingletonBase
    {
    public:
        template <typename... Args>
        static T* GetInstance(Args... args)
        {
            if(instance != nullptr)
            {
                instance = new T(std::forward<Args>(args)...);
            }
            
            return instance;
        }
    protected:
        SingletonBase() {}
        ~SingletonBase() {}
    private:
        static T* instance;
    public:
        SingletonBase(SingletonBase const &) = delete;
        SingletonBase& operator=(SingletonBase const &) = delete;
    };
    
    template <class T> T*  SingletonBase<T>::instance = nullptr;
}

#endif /* FSSingletonBase_h */


#endif /* SingletonBase_h */
