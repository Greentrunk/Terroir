#include "VertexBuffer.h"
#include "../Renderer.h"
#include "Tpch.h"
#include "core/Assert.h"
#include "log/Log.h"
#include "renderer/opengl/OpenGLVertexBuffer.h"

namespace Terroir
{
VertexBuffer *VertexBuffer::Create(f32 *vertices, u32 size)
{
    switch (Renderer::GetRenderAPI())
    {
    case RendererAPI::None: {
        TERR_ASSERT(false, "RendererAPI::None is not support in Terroir!");
        return nullptr;
    }

    case RendererAPI::OpenGL: {
        return new OpenGLVertexBuffer(vertices, size);
    }

    default: {

        TERR_ENGINE_ERROR("Unkown RendererAPI");
        return nullptr;
    }
    }
}

} // namespace Terroir
