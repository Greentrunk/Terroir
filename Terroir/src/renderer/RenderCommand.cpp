#include "RenderCommand.h"
#include "Tpch.h"
#include "renderer/opengl/OpenGLRendererAPI.h"

namespace Terroir
{

std::unique_ptr<RendererAPI> RenderCommand::s_RendererAPI{std::make_unique<OpenGLRendererAPI>()};
}
