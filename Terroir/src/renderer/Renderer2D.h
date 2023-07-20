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
#include "Terroir/src/renderer/renderable/font/Font.h"
#include "Terroir/src/renderer/shader/Shader.h"
#include "Terroir/src/renderer/shader/ShaderLibrary.h"
#include "Terroir/src/renderer/texture/Texture2D.h"

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

    static void DrawText(const std::string &, Vec3 &, const Vec2 &, const Vec4 &, f32 rotation = 0.0f);

    struct Stats
    {
        u32 m_DrawCalls{0};
        u32 m_RectCount{0};

        [[nodiscard]] constexpr u32 GetTotalVertexCount() const
        {
            return m_RectCount * 4;
        }
        [[nodiscard]] constexpr u32 GetTotalIndexCount() const
        {
            return m_RectCount * 6;
        }
    };

    // Resets the renderer statistics
    static void ResetStats();

    [[nodiscard]] static Stats GetStats();

  private:
    static void FlushAndReset();
    static void SetRectVertexBufferData(const Mat4&, const Vec4&, std::array<Vec2, 4>, f32, f32, u32);
};

struct RectVertex
{
    Vec3 m_Position;
    Vec4 m_Color;
    Vec2 m_TexCoord;
    f32 m_TexIndex;
    f32 m_TilingFactor;
};

struct Renderer2DData
{
    std::shared_ptr<VertexArray> m_RECT_VAO;
    std::shared_ptr<VertexBuffer> m_RECT_VBO;
    std::shared_ptr<IndexBuffer> m_RECT_IBO;
    ShaderLibrary m_ShaderLibrary;
    std::shared_ptr<Texture2D> m_WhiteTexture;
    std::shared_ptr<Font> m_Font;
    std::shared_ptr<VertexArray> m_fVAO;
    std::shared_ptr<VertexBuffer> m_fVBO;

    static const u32 MAX_RECTS = 20000;
    static const u32 MAX_VERTICES = MAX_RECTS * 4;
    static const u32 MAX_INDICES = MAX_RECTS * 6;
    static const u32 MAX_TEXTURE_SLOTS = 32;

    // Keep track of the current index in the buffer
    u32 m_RectIndexCount = 0;

    std::shared_ptr<RectVertex[]> m_RectVertexBufferBase;
    RectVertex *m_RectVertexBufferPtr{nullptr}; // Pointer to the current position in the buffer

    std::array<std::shared_ptr<Texture2D>, MAX_TEXTURE_SLOTS> m_TextureSlots;
    u32 m_TextureSlotIndex = 1; // 0 is reserved for white texture

    std::array<Vec4, 4> m_RectVertexPositions;

    Renderer2D::Stats m_Stats;
};

} // namespace Terroir

#endif // TERROIR_RENDERER2D_H
