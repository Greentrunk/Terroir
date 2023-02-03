#include "VertexArray.h"
#include "Tpch.h"
#include "core/Assert.h"
#include "opengl/OpenGLVertexArray.h"
#include "renderer/Renderer.h"
#include "renderer/RendererAPI.h"
namespace Terroir
{
std::shared_ptr<VertexArray> VertexArray::Create()
{
    using enum RendererAPI::API;
    switch (Renderer::GetAPI())
    {
    case None: {
        TERR_ASSERT(false, "RendererAPI::None is not supported in Terroir!");
        return nullptr;
    }

    case OpenGL: {
        return std::make_shared<OpenGLVertexArray>();
    }

    default: {

        TERR_ENGINE_ERROR("Unknown RendererAPI");
        return nullptr;
    }
    }
}
} // namespace Terroir
