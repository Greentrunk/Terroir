#ifndef TERROIR_BUFFERLAYOUT_H
#define TERROIR_BUFFERLAYOUT_H

#include "Terroir/src/core/Types.h"
#include "Terroir/src/log/Log.h"

namespace Terroir
{

enum class ShaderDataType
{
    None = 0,
    Vec,
    Vec2,
    Vec3,
    Vec4,
    Mat3,
    Mat4,
    I,
    I2,
    I3,
    I4,
    Bool
};

static constexpr u32 ShaderDataTypeSize(ShaderDataType type)
{
    using enum ShaderDataType;
    switch (type)
    {
    case Vec:
        return 4;
    case Vec2:
        return 4 * 2;
    case Vec3:
        return 4 * 3;
    case Vec4:
        return 4 * 4;
    case Mat3:
        return 4 * 3 * 3;
    case Mat4:
        return 4 * 4 * 4;
    case I:
        return 4;
    case I2:
        return 4 * 2;
    case I3:
        return 4 * 3;
    case I4:
        return 4 * 4;
    case Bool:
        return 4;
    default:
        TERR_ENGINE_ERROR("Unknown ShaderDataType!");
        return 0;
    }
}

class BufferElement
{
    friend class BufferLayout;

  public:
    BufferElement() = default;
    BufferElement(std::string name, ShaderDataType type, bool normalized = false)
        : m_Name(std::move(name)), m_Size(ShaderDataTypeSize(type)), m_Type(type), m_Normalized(normalized)
    {
    }

    [[nodiscard]] constexpr ShaderDataType GetShaderDataType() const
    {
        return m_Type;
    }

    [[nodiscard]] constexpr bool IsNormalized() const
    {
        return m_Normalized;
    }

    [[nodiscard]] constexpr u32 GetOffset() const
    {
        return m_Offset;
    }

    [[nodiscard]] constexpr u32 GetComponentCount() const
    {
        using enum ShaderDataType;
        switch (m_Type)
        {
        case Vec:
            return 1;
        case Vec2:
            return 2;
        case Vec3:
            return 3;
        case Vec4:
            return 4;
        case Mat3:
            return 3 * 3;
        case Mat4:
            return 4 * 4;
        case I:
            return 1;
        case I2:
            return 2;
        case I3:
            return 3;
        case I4:
            return 4;
        case Bool:
            return 1;
        default:
            TERR_ENGINE_ERROR("Unknown ShaderDataType!");
            return 0;
        }
    }

  private:
    std::string m_Name;
    u32 m_Offset{0};
    u32 m_Size{};
    ShaderDataType m_Type{ShaderDataType::None};
    bool m_Normalized{};
};

class BufferLayout
{
    using BufferElementVec = std::vector<BufferElement>;
    using BufferElementIterator = BufferElementVec::iterator;
    using BufferElementConstIterator = BufferElementVec::const_iterator;

  public:
    BufferLayout() = default;
    BufferLayout(const std::initializer_list<BufferElement> &elements) : m_Elements(elements)
    {
        CalaculateOffsetsAndStride();
    }
    [[nodiscard]] constexpr BufferElementVec GetElements() const
    {
        return m_Elements;
    }

    [[nodiscard]] constexpr u32 GetStride() const
    {
        return m_Stride;
    }

    inline BufferElementIterator begin()
    {
        return m_Elements.begin();
    }

    inline BufferElementIterator end()
    {
        return m_Elements.end();
    }

    [[nodiscard]] constexpr BufferElementConstIterator begin() const
    {
        return m_Elements.begin();
    }

    [[nodiscard]] constexpr BufferElementConstIterator end() const
    {
        return m_Elements.end();
    }

  private:
    void CalaculateOffsetsAndStride()
    {
        u32 offset{0};
        for (auto &element : m_Elements)
        {
            element.m_Offset = offset;
            offset += element.m_Size;
            m_Stride += element.m_Size;
        }
    }
    BufferElementVec m_Elements;
    u32 m_Stride{0};
};

}; // namespace Terroir

#endif //
TERROIR_BUFFERLAYOUT_H
