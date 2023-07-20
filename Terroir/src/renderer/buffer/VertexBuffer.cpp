#include "VertexBuffer.h"
#include "../Renderer.h"
#include "Tpch.h"
#include "core/Assert.h"
#include "log/Log.h"
#include "renderer/opengl/OpenGLVertexBuffer.h"

namespace Terroir
{
std::shared_ptr<VertexBuffer> VertexBuffer::Create(f32 *vertices, u32 size, bool dyn)
{
    using enum RendererAPI::API;
    switch (Renderer::GetAPI())
    {
    case None: {
        TERR_ASSERT(false, "RendererAPI::None is not support in Terroir!");
        return nullptr;
    }

    case OpenGL: {
        return std::make_shared<OpenGLVertexBuffer>(vertices, size, dyn);
    }

    default: {

        TERR_ENGINE_ERROR("Unknown RendererAPI");
        return nullptr;
    }
    }
}

std::shared_ptr<VertexBuffer> VertexBuffer::Create(u32 size)
{
    using enum RendererAPI::API;
    switch (Renderer::GetAPI())
    {
    case None: {
        TERR_ASSERT(false, "RendererAPI::None is not support in Terroir!");
        return nullptr;
    }

    case OpenGL: {
        return std::make_shared<OpenGLVertexBuffer>(size);
    }

    default: {

        TERR_ENGINE_ERROR("Unknown RendererAPI");
        return nullptr;
    }
    }
}

} // namespace Terroir
