////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Christopher J. Pohl 2023 to Present  All Rights Reserved.
//
// This file is part of TERROIR ENGINE:
// This is free software as described by the Apache 2.0 License
//
// The above copyright notice shall be included in all portions of this software
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

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
std::shared_ptr<Texture2D> Texture2D::Create(u32 width, u32 height)
{
    using enum RendererAPI::API;
    switch (Renderer::GetAPI())
    {
    case None: {
        TERR_ASSERT(false, "RendererAPI::None is not supported in Terroir!");
        return nullptr;
    }

    case OpenGL: {
        return std::make_shared<OpenGLTexture2D>(width, height);

    default: {

        TERR_ENGINE_ERROR("Unknown RendererAPI");
        return nullptr;
    }
    }
    }
}
} // namespace Terroir