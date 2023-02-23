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

#include <Terroir.h>
#include <imgui.h>

using namespace Terroir;
constexpr const i32 NUM_TIMES_TO_SUBDIVIDE{5};
constexpr const i32 NUM_TRIANGLES{729};
constexpr const i32 NUM_VERTICES{NUM_TRIANGLES * 3};

std::array<Vec2, NUM_VERTICES> points;
i32 index{0};

class TestLayer : public Layer
{
  public:
    explicit TestLayer(const std::string_view &name)
        : Layer(name), m_CameraController(1200.0f / 720.0f), m_SquarePos(0.0f)

    {
        std::array<f32, 3 * 7> vertices{-0.5f, -0.5f, 0.0f, 0.0f, 0.8f, 0.0f, 1.0f, 0.5f, -0.5f, 0.0f, 0.0f,
                                        0.8f,  0.0f,  1.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.8f, 0.0f,  1.0f};
        std::array<u32, 3> indices{0, 1, 2};

        m_VertexArray = VertexArray::Create();
        auto vertexBuffer = VertexBuffer::Create(&vertices[0], sizeof(vertices));

        BufferLayout layout{{"a_Position", ShaderDataType::Vec3}, {"a_Color", ShaderDataType::Vec4}};
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        auto indexBuffer = IndexBuffer::Create(&indices[0], static_cast<u32>(indices.size()));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        vertexBuffer->Unbind();
        m_VertexArray->Unbind();

        m_SquareVertexArray = VertexArray::Create();

        //        auto shader1{m_ShaderLibrary.Load()};

        std::array<f32, 5 * 4> vertices2{-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,

                                         0.5f,  0.5f,  0.0f, 1.0f, 1.0f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f};
        auto squareBufferArray{VertexBuffer::Create(&vertices2[0], sizeof(vertices2))};
        squareBufferArray->SetLayout({{"a_Pos", ShaderDataType::Vec3}, {"a_TexCoord", ShaderDataType::Vec2}});
        m_SquareVertexArray->AddVertexBuffer(squareBufferArray);

        std::array<u32, 6> indices2{0, 1, 2, 2, 3, 0};
        auto ib2{IndexBuffer::Create(&indices2[0], static_cast<u32>(indices2.size()))};
        m_SquareVertexArray->SetIndexBuffer(ib2);

        auto textureShader = m_ShaderLibrary.Load("Texture", {"Terroir/src/renderer/shader/TextureVertexShader.glsl",
                                                              "Terroir/src/renderer/shader/TextureFragShader.glsl"});
        const std::filesystem::path path{"Sandbox/assets/textures/gigachad.jpg"};
        m_Texture = Texture2D::Create(path);

        const std::filesystem::path logoPath{"Sandbox/assets/textures/logo.png"};
        m_LogoTexture = Texture2D::Create(logoPath);
        // BAD
        // std::dynamic_pointer_cast<OpenGLShader>(m_LogoTexture)->Bind();
        // std::dynamic_pointer_cast<OpenGLShader>(m_LogoTexture)->UploadUniform("u_Texture", 0);

        std::dynamic_pointer_cast<OpenGLShader>(textureShader)->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(textureShader)->UploadUniform("u_Texture", 0);
    };

    ~TestLayer() override
    {
        TERR_APP_DEBUG("DELETING LAYER");
    }

    void OnUpdate(Timestep dt) override
    {
        // Update
        m_CameraController.OnUpdate(dt);

        RenderCommand::Clear({.1, 1, .6, 1});
        Renderer::BeginScene(m_CameraController.GetCamera());
        //        auto shader{m_ShaderLibrary.Get("Default")};
        //        Renderer::Submit(m_VertexArray, shader, Math::Transform::Scale(Mat4{1.0f}, Vec3{1.5f}));
        m_Texture->Bind();

        // square
        auto textureShader{m_ShaderLibrary.Get("Texture")};
        Renderer::Submit(m_SquareVertexArray, textureShader, Math::Transform::Scale(Mat4{1.0f}, Vec3{1.5f}));
        m_LogoTexture->Bind();
        Renderer::Submit(m_SquareVertexArray, textureShader, Math::Transform::Scale(Mat4{1.0f}, Vec3{1.5f}));

        Renderer::EndScene();
    }

    void OnEvent(Event &e) override
    {
        m_CameraController.OnEvent(e);

        // if event type is window resize event then set zoom level
        if (e.GetEventType() == EventType::WindowResize)
        {
            // We will see about this later
            //            auto &event{dynamic_cast<WindowResizeEvent &>(e)};
            //            auto zoom{static_cast<f32>(event.GetWidth()) / 1200.0f};
            //            m_CameraController.SetZoomLevel(zoom);
        }
    }

    void OnDearImGuiRender() override
    {
        ImGui::Begin("Hi");
        ImGui::End();
    }

  private:
    ShaderLibrary m_ShaderLibrary;
    std::shared_ptr<VertexArray> m_VertexArray;
    OrthographicCameraController m_CameraController;
    std::shared_ptr<VertexArray> m_SquareVertexArray;
    std::shared_ptr<Texture2D> m_Texture;
    std::shared_ptr<Texture2D> m_LogoTexture;
    Vec3 m_SquarePos;
};

class SandboxGame : public Application
{
  public:
    SandboxGame(const std::string_view &name, u32 width, u32 height)
    {
        // shut the warnings up
        TERR_APP_DEBUG("THIS IS TO SHUT OFF COMPILER WARNINGS, {}{}{}", name, width, height);
        PushLayer(std::make_unique<TestLayer>("TEST"));
    }
};

std::unique_ptr<Application> Terroir::CreateApplication()
{
    TERR_APP_INFO("Game Initialized!");
    return std::make_unique<SandboxGame>("Test", 1000, 1000);
}
