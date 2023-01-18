#include "RenderCommand.h"
#include "Tpch.h"
#include "renderer/opengl/OpenGLRendererAPI.h"

namespace Terroir
{

RendererAPI *RenderCommand::s_RendererAPI{new OpenGLRendererAPI};
}
