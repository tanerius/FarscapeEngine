#pragma once

#include "RendererAPI.h"

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
        case ShaderDataType::Bool:          return 1;
        }

        FS_CORE_ASSERT(false, "Unknown ShaderDataTypeSize!");
        return 0;
    }

    struct BufferElement
    {
        std::string Name;
        ShaderDataType Type;
        uint32_t Size;
        uint32_t Offset;
        bool Normalized;

        BufferElement() = default;

        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
            : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
        {
        }

        uint32_t GetComponentCount() const
        {
            switch (Type)
            {
            case ShaderDataType::Float:   return 1;
            case ShaderDataType::Float2:  return 2;
            case ShaderDataType::Float3:  return 3;
            case ShaderDataType::Float4:  return 4;
            case ShaderDataType::Mat3:    return 3 * 3;
            case ShaderDataType::Mat4:    return 4 * 4;
            case ShaderDataType::Int:     return 1;
            case ShaderDataType::Int2:    return 2;
            case ShaderDataType::Int3:    return 3;
            case ShaderDataType::Int4:    return 4;
            case ShaderDataType::Bool:    return 1;
            }

            FS_CORE_ASSERT(false, "Unknown ShaderDataType!");
            return 0;
        }
    };

    class BufferLayout : public IBufferLayout
    {
    public:
        BufferLayout() {}

        BufferLayout(const std::initializer_list<BufferElement>& elements)
            : m_Elements(elements)
        {
            CalculateOffsetsAndStride();
        }

        inline uint32_t GetStride() const { return m_Stride; }
        inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

        std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
        std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
    private:
        void CalculateOffsetsAndStride()
        {
            uint32_t offset = 0;
            m_Stride = 0;
            for (auto& element : m_Elements)
            {
                element.Offset = offset;
                offset += element.Size;
                m_Stride += element.Size;
            }
        }
    private:
        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride = 0;
    };

    enum class VertexBufferUsage
    {
        None = 0, Static = 1, Dynamic = 2
    };

    class VertexBuffer : public RefCounter
    {
    public:
        virtual ~VertexBuffer() {}

        virtual void SetData(void* buffer, uint32_t size, uint32_t offset = 0) = 0;
        virtual void Bind() const = 0;

        virtual const BufferLayout& GetLayout() const = 0;
        virtual void SetLayout(const BufferLayout& layout) = 0;

        virtual unsigned int GetSize() const = 0;
        virtual RendererID GetRendererID() const = 0;

        static SharedRef<VertexBuffer> Create(void* data, uint32_t size, VertexBufferUsage usage = VertexBufferUsage::Static);
        static SharedRef<VertexBuffer> Create(uint32_t size, VertexBufferUsage usage = VertexBufferUsage::Dynamic);
    };

    class IndexBuffer : public RefCounter
    {
    public:
        virtual ~IndexBuffer() {}

        virtual void SetData(void* buffer, uint32_t size, uint32_t offset = 0) = 0;
        virtual void Bind() const = 0;

        virtual uint32_t GetCount() const = 0;

        virtual unsigned int GetSize() const = 0;
        virtual RendererID GetRendererID() const = 0;

        static SharedRef<IndexBuffer> Create(void* data, uint32_t size = 0);
    };

}
