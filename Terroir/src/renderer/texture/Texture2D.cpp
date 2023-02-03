#include "Texture2D.h"
#include "Tpch.h"
#include "core/Assert.h"
#include "renderer/Renderer.h"
#include "renderer/RendererAPI.h"
#include "renderer/opengl/OpenGLTexture.h"

namespace Terroir
{
std::shared_ptr<Texture2D> Texture2D::Create(const std::filesystem::path &path)
{
    using enum RendererAPI::API;
    switch (Renderer::GetAPI())
    {
    case None: {
        TERR_ASSERT(false, "RendererAPI::None is not supported in Terroir!");
        return nullptr;
    }

    case OpenGL: {
        return std::make_shared<OpenGLTexture2D>(path);

    default: {

        TERR_ENGINE_ERROR("Unknown RendererAPI");
        return nullptr;
    }
    }
    }
}
} // namespace Terroir