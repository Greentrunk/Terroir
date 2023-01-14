#include "Tpch.h"
#include "core/Assert.h"
#include "renderer/Renderer.h"
#include "VertexArray.h"
#include "opengl/OpenGLVertexArray.h"
namespace Terroir {
VertexArray* VertexArray::Create() {
  switch (Renderer::GetRenderAPI())
    {
    case RendererAPI::None: {
        TERR_ASSERT(false, "RendererAPI::None is not support in Terroir!");
        return nullptr;
    }

    case RendererAPI::OpenGL: {
        return new OpenGLVertexArray();
    }

    default: {

        TERR_ENGINE_ERROR("Unkown RendererAPI");
        return nullptr;
    }
    }

}
}
