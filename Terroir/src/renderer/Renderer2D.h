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

#ifndef TERROIR_RENDERER2D_H
#define TERROIR_RENDERER2D_H

#include "Terroir/src/renderer/VertexArray.h"
#include "Terroir/src/renderer/camera/OrthographicCamera.h"
#include "Terroir/src/renderer/renderable/Sprite.h"
#include "Terroir/src/renderer/shader/Shader.h"
#include "Terroir/src/renderer/texture/Texture2D.h"
#include "Terroir/src/renderer/shader/ShaderLibrary.h"

namespace Terroir
{

// Base 2D Renderer
class Renderer2D
{
  public:
    ~Renderer2D();
    static void Init();
    static void Shutdown();
    static void BeginScene(const OrthographicCamera &);
    static void EndScene();
    static void Flush();
    static void DrawRect(const Vec2 &, const Vec2 &, const Vec4 &, f32 rotation = 0.0f);
    static void DrawRect(const Vec3 &, const Vec2 &, const Vec4 &, f32 rotation = 0.0f);
    static void DrawSprite(const Sprite &);
    //    static void DrawSprite(const Vec2 &, const Vec2 &, const std::shared_ptr<Texture2D> &, f32 rotation = 0.0f,
    //                         const Vec4 &tintColor = {1.0f, 1.0f, 1.0f, 1.0f}, f32 tileFactor = 1.0f);
    //    static void DrawSprite(const Vec3 &, const Vec2 &, const std::shared_ptr<Texture2D> &, const Vec4 &);
    //    static void DrawSprite(const Vec3 &, const Vec2 &, const std::shared_ptr<SubTexture2D> &);
    //    static void DrawSprite(const Vec3 &, const Vec2 &, const std::shared_ptr<SubTexture2D> &, const Vec4 &);
    //    &);
    //    static void DrawSprite(const Vec3 &, const Vec2 &, const std::shared_ptr<Shader> &, const Vec4 &);
    //    static void DrawSprite(const Vec3 &, const Vec2 &, const std::shared_ptr<Shader> &,
    //                         const std::shared_ptr<Texture2D> &);
    //    static void DrawSprite(const Vec3 &, const Vec2 &, const std::shared_ptr<Shader> &,
    //                         const std::shared_ptr<Texture2D> &, const Vec4 &);
    //    static void DrawSprite(const Vec3 &, const Vec2 &, const std::shared_ptr<Shader> &, const
    //    std::shared_ptr<SubTexture2D> &); static void DrawSprite(const Vec3 &, const Vec2 &, const
    //    std::shared_ptr<Shader> &, const std::shared_ptr<SubTexture2D> &,
    // const Vec4 &);
};

struct Renderer2DData
{
    std::shared_ptr<VertexArray> m_QUAD_VAO;
    std::shared_ptr<VertexBuffer> m_QUAD_VBO;
    std::shared_ptr<IndexBuffer> m_QUAD_IBO;
    std::shared_ptr<Shader> m_TextureShader;
    ShaderLibrary m_ShaderLibrary;
    std::shared_ptr<Texture2D> m_WhiteTexture;
};

} // namespace Terroir

#endif // TERROIR_RENDERER2D_H
