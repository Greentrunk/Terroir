#include "RendererAPI.h"
#include "Tpch.h"

namespace Terroir
{
// Later will contain different graphics backends per platform
RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

} // namespace Terroir
