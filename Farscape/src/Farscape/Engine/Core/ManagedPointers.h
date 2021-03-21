#pragma once

#include <stdint.h>

namespace Farscape
{

    class RefCounter
    {
    public:
        void IncRefCount() const
        {
            m_RefCount++;
        }
        void DecRefCount() const
        {
            m_RefCount--;
        }

        uint32_t GetRefCount() const { return m_RefCount; }
    private:
        mutable uint32_t m_RefCount = 0; // TODO: atomic
    };


    template<typename T>
    class SharedRef
    {
    public:
        SharedRef()
            : m_Instance(nullptr)
        { 
        }

        SharedRef(std::nullptr_t n)
            : m_Instance(nullptr)
        {
        }

        SharedRef(T* instance)
            : m_Instance(instance)
        {
            static_assert(std::is_base_of<RefCounter, T>::value, "Class must inherit from RefCounter!");

            IncRef();
        }

        template<typename T2>
        SharedRef(const SharedRef<T2>& other)
        {
            m_Instance = other.m_Instance;
            IncRef();
        }

        template<typename T2>
        SharedRef(SharedRef<T2>&& other)
        {
            m_Instance = other.m_Instance;
            other.m_Instance = nullptr;
        }

        ~SharedRef()
        {
            DecRef();
        }

        SharedRef(const SharedRef<T>& other)
            : m_Instance(other.m_Instance)
        {
            IncRef();
        }

        SharedRef& operator=(std::nullptr_t)
        {
            DecRef();
            m_Instance = nullptr;
            return *this;
        }

        SharedRef& operator=(const SharedRef<T>& other)
        {
            other.IncRef();
            DecRef();

            m_Instance = other.m_Instance;
            return *this;
        }

        template<typename T2>
        SharedRef& operator=(const SharedRef<T2>& other)
        {
            other.IncRef();
            DecRef();

            m_Instance = other.m_Instance;
            return *this;
        }

        template<typename T2>
        SharedRef& operator=(SharedRef<T2>&& other)
        {
            DecRef();

            m_Instance = other.m_Instance;
            other.m_Instance = nullptr;
            return *this;
        }

        operator bool() { return m_Instance != nullptr; }
        operator bool() const { return m_Instance != nullptr; }

        T* operator->() { return m_Instance; }
        const T* operator->() const { return m_Instance; }

        T& operator*() { return *m_Instance; }
        const T& operator*() const { return *m_Instance; }

        T* Raw() { return  m_Instance; }
        const T* Raw() const { return  m_Instance; }

        void Reset(T* instance = nullptr)
        {
            DecRef();
            m_Instance = instance;
        }

        template<typename... Args>
        static SharedRef<T> Create(Args&&... args)
        {
            return SharedRef<T>(new T(std::forward<Args>(args)...));
        }
    private:
        void IncRef() const
        {
            if (m_Instance)
                m_Instance->IncRefCount();
        }

        void DecRef() const
        {
            if (m_Instance)
            {
                m_Instance->DecRefCount();
                if (m_Instance->GetRefCount() == 0)
                {
                    delete m_Instance;
                }
            }
        }

        template<class T2>
        friend class SharedRef;
        T* m_Instance;
    };

    // TODO: WeakRef

}