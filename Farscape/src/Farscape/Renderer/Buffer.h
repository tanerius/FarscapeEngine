#pragma once
#include "Core/Core.h"

namespace Farscape {

    enum class ShaderDataType : uint8_t
    {
        None = 0,
        Float = 1,
        Float2 = 2,
        Float3 = 3,
        Float4 = 4,
        Mat3 = 5,
        Mat4 = 6,
        Int = 7,
        Int2 = 8,
        Int3 = 9,
        Int4 = 10,
        Bool = 11
    };

    // a simple converter function to get size of our types in bytes
    static uint32_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::None:          return 0;
            case ShaderDataType::Float:         return 4; // in bytes
            case ShaderDataType::Float2:        return 4 * 2; 
            case ShaderDataType::Float3:        return 4 * 3;
            case ShaderDataType::Float4:        return 4 * 4;
            case ShaderDataType::Mat3:          return 4 * 3 * 3;
            case ShaderDataType::Mat4:          return 4 * 4 * 4;
            case ShaderDataType::Int:           return 4;
            case ShaderDataType::Int2:          return 4 * 2;
            case ShaderDataType::Int3:          return 4 * 3;
            case ShaderDataType::Int4:          return 4 * 4;
            case ShaderDataType::Bool:          return 4;
        }

        FS_CORE_ASSERT(false, "Unknown ShaderDataTypeSize!");
        return 0;
    }

    struct BufferElement
    {
        std::string name;
        uint32_t offset;
        uint32_t size;
        ShaderDataType type;
        bool normalized;

        BufferElement(
            ShaderDataType _type,
            const std::string& _name,
            const bool _normalized = false
        )
            : name(_name)
            , offset(0)
            , size(ShaderDataTypeSize(_type))
            , type(_type)
            , normalized(_normalized)
        { }

        uint32_t GetComponentCount() const
        {
            switch (type)
            {
                case ShaderDataType::None:      return 0;
                case ShaderDataType::Float:     return 1;
                case ShaderDataType::Float2:    return 2;
                case ShaderDataType::Float3:    return 3;
                case ShaderDataType::Float4:    return 4;
                case ShaderDataType::Mat3:      return 3 * 3;
                case ShaderDataType::Mat4:      return 4 * 4;
                case ShaderDataType::Int:       return 1;
                case ShaderDataType::Int2:      return 2;
                case ShaderDataType::Int3:      return 3;
                case ShaderDataType::Int4:      return 4;
                case ShaderDataType::Bool:      return 1;
            }

            FS_CORE_ASSERT(false, "Unknown ShaderDataType in GetElementCount!");
            return 0;
        }
    };
    
    // A class to describe the layout of a buffer 
    class BufferLayout : public IBufferLayout
    {
    public:
        BufferLayout() {}
        BufferLayout(const std::initializer_list<BufferElement>& element) 
            : m_Elements(element)
        { 
            CalculateOffsetsAndStride();
        }

        inline const std::vector<BufferElement>& GetEmelents() const { return m_Elements;  }
        inline uint32_t GetStride() const { return m_strideOffset; }
        
        std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
        std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
    private:
        void CalculateOffsetsAndStride()
        {
            uint32_t offset = 0;
            m_strideOffset = 0;
            for (auto& element : m_Elements)
            {
                element.offset = offset;
                offset += element.size;
                m_strideOffset += element.size;
            }
        }
    private:
        std::vector<BufferElement> m_Elements;
        uint32_t m_strideOffset = 0;
    };

    class VertexBuffer : public IBuffer
    {
    public:
        virtual ~VertexBuffer() {}

        virtual void SetLayout(const BufferLayout& layout) = 0;
        virtual const BufferLayout& GetLayout() const = 0;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;


        // Shouold not belong  to 
        static VertexBuffer* Create(float* vertices, uint32_t arraySize);
    };

    class IndexBuffer : public IBuffer 
    {
    public:
        virtual ~IndexBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetCount() const = 0;

        // Shouold not belong  to 
        static IndexBuffer* Create(uint32_t* indices, uint32_t count);
    };

}
