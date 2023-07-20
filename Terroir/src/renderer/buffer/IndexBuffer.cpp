#include "IndexBuffer.h"
#include "../Renderer.h"
#include "Tpch.h"
#include "core/Assert.h"
#include "log/Log.h"
#include "renderer/RendererAPI.h"
#include "renderer/opengl/OpenGLIndexBuffer.h"

namespace Terroir
{
std::shared_ptr<IndexBuffer> IndexBuffer::Create(u32 *indices, u32 count)
{
    using enum RendererAPI::API;
    switch (Renderer::GetAPI())
    {
    case None: {
        TERR_ASSERT(false, "RendererAPI::None is not support in Terroir!");
        return nullptr;
    }

    case OpenGL: {
        return std::make_shared<OpenGLIndexBuffer>(indices, count);
    }

    default: {

        TERR_ENGINE_ERROR("Unkown RendererAPI");
        return nullptr;
    }
    }
}

} // namespace Terroir
