#include "IndexBuffer.h"
#include "../Renderer.h"
#include "Tpch.h"
#include "core/Assert.h"
#include "log/Log.h"
#include "renderer/opengl/OpenGLIndexBuffer.h"

namespace Terroir
{
IndexBuffer *IndexBuffer::Create(u32 *indices, u32 size)
{
    switch (Renderer::GetRenderAPI())
    {
    case RendererAPI::None: {
        TERR_ASSERT(false, "RendererAPI::None is not support in Terroir!");
        return nullptr;
    }

    case RendererAPI::OpenGL: {
        return new OpenGLIndexBuffer(indices, size);
    }

    default: {

        TERR_ENGINE_ERROR("Unkown RendererAPI");
        return nullptr;
    }
    }
}

} // namespace Terroir
