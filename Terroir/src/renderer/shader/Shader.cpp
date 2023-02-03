#include "Shader.h"
#include "Tpch.h"
#include "core/Assert.h"
#include "renderer/Renderer.h"
#include "renderer/RendererAPI.h"
#include "renderer/opengl/OpenGLShader.h"
namespace Terroir
{

std::unique_ptr<Shader> Shader::Create()
{
    using enum RendererAPI::API;
    switch (Renderer::GetAPI())
    {
    case None: {
        TERR_ENGINE_ASSERT(false, "RendererAPI::None is not supported in Terroir!");
    }
    case OpenGL: {
        return std::make_unique<OpenGLShader>();
    }
    default:

        TERR_ENGINE_ERROR("Unknown RendererAPI");
        return nullptr;
    }
}

std::unique_ptr<Shader> Shader::Create(const char *vertexPath, const char *fragPath)
{
    using enum RendererAPI::API;
    switch (Renderer::GetAPI())
    {
    case None: {
        TERR_ENGINE_ASSERT(false, "RendererAPI::None is not supported in Terroir!");
    }
    case OpenGL: {
        return std::make_unique<OpenGLShader>(vertexPath, fragPath);
    }
    default:

        TERR_ENGINE_ERROR("Unknown RendererAPI");
        return nullptr;
    }
}

} // namespace Terroir