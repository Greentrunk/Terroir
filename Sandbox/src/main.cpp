#include <Terroir.h>
#include <imgui.h>

using namespace Terroir;
class TestLayer : public Layer
{
  public:
    explicit TestLayer(const std::string_view &name)
        : Layer(name), m_Camera(-1.f, 1.f, -1.f, 1.f), m_CameraPos(0.0f), m_SquarePos(0.0f)

    {
        std::array<f32, 3 * 7> vertices{-0.5f, -0.5f, 0.0f, 0.0f, 0.8f, 0.0f, 1.0f, 0.5f, -0.5f, 0.0f, 0.0f,
                                        0.8f,  0.0f,  1.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.8f, 0.0f,  1.0f};
        std::array<u32, 3> indices{0, 1, 2};

        m_VertexArray = VertexArray::Create();
        auto vertexBuffer = VertexBuffer::Create(&vertices[0], sizeof(vertices));

        BufferLayout layout{{"a_Pos", ShaderDataType::Vec3}, {"a_Color", ShaderDataType::Vec4}};
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        auto indexBuffer = IndexBuffer::Create(&indices[0], static_cast<u32>(indices.size()));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        vertexBuffer->Unbind();
        m_VertexArray->Unbind();

        m_SquareVertexArray = VertexArray::Create();

        m_Shader = Shader::Create();

        std::array<f32, 5 * 4> vertices2{-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,

                                         0.5f,  0.5f,  0.0f, 1.0f, 1.0f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f};
        auto squareBufferArray{VertexBuffer::Create(&vertices2[0], sizeof(vertices2))};
        squareBufferArray->SetLayout({{"a_Pos", ShaderDataType::Vec3}, {"a_TexCoord", ShaderDataType::Vec2}});
        m_SquareVertexArray->AddVertexBuffer(squareBufferArray);

        std::array<u32, 6> indices2{0, 1, 2, 2, 3, 0};
        auto ib2{IndexBuffer::Create(&indices2[0], static_cast<u32>(indices2.size()))};
        m_SquareVertexArray->SetIndexBuffer(ib2);

        m_Shader2 = Shader::Create({"Terroir/src/renderer/shader/VertexShader2.glsl",
                                   "Terroir/src/renderer/shader/FragShader2.glsl"});

        m_TextureShader = Shader::Create({"Terroir/src/renderer/shader/TextureVertexShader.glsl",
                                         "Terroir/src/renderer/shader/TextureFragShader.glsl"});
        const std::filesystem::path path{"Sandbox/assets/textures/gigachad.jpg"};
        m_Texture = Texture2D::Create(path);

        const std::filesystem::path logoPath{"Sandbox/assets/textures/logo.png"};
        m_LogoTexture = Texture2D::Create(logoPath);
        // BAD
        // std::dynamic_pointer_cast<OpenGLShader>(m_LogoTexture)->Bind();
        // std::dynamic_pointer_cast<OpenGLShader>(m_LogoTexture)->UploadUniform("u_Texture", 0);

        std::dynamic_pointer_cast<OpenGLShader>(m_TextureShader)->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(m_TextureShader)->UploadUniform("u_Texture", 0);
    }

    ~TestLayer() override
    {
        TERR_APP_DEBUG("DELETING LAYER");
    }

    void OnUpdate(Timestep dt) override
    {
        if (Input::IsKeyPressed(TERR_KEY_LEFT))
        {
            m_CameraPos.x -= m_CameraVelocity * dt;
        }

        if (Input::IsKeyPressed(TERR_KEY_RIGHT))
        {
            m_CameraPos.x += m_CameraVelocity * dt;
        }

        if (Input::IsKeyPressed(TERR_KEY_DOWN))
        {
            m_CameraPos.y -= m_CameraVelocity * dt;
        }
        if (Input::IsKeyPressed(TERR_KEY_UP))
        {
            m_CameraPos.y += m_CameraVelocity * dt;
        }

        RenderCommand::Clear({.2, .5, .4, 1});

        // m_Camera.SetRotation(glfwGetTime() * 100.f);
        m_Camera.SetPosition(m_CameraPos);
        Renderer::BeginScene(m_Camera);

        Mat4 scale{Math::Transform::Scale(Mat4(1.0f), Vec3(0.1f))};

        std::dynamic_pointer_cast<OpenGLShader>(m_Shader2)->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(m_Shader2)->UploadUniform(
            "u_Color", Vec3{m_SquareColor[0], m_SquareColor[1], m_SquareColor[2]});

        for (auto y = 0; y != 10; ++y)
        {
            for (auto x = 0; x != 10; ++x)
            {
                Vec3 pos(x * 0.12f, y * 0.12f, 0.0f);
                Mat4 transform = Math::Transform::Translate(Mat4(1.0f), pos) * scale;
                Renderer::Submit(m_SquareVertexArray, m_Shader2, transform);
            }
        }
        m_Texture->Bind();
        // square
        Renderer::Submit(m_SquareVertexArray, m_TextureShader, Math::Transform::Scale(Mat4{1.0f}, Vec3{1.5f}));
        m_LogoTexture->Bind();
        Renderer::Submit(m_SquareVertexArray, m_TextureShader, Math::Transform::Scale(Mat4{1.0f}, Vec3{1.5f}));

        // TRIANGLE
        // Renderer::Submit(m_VertexArray, m_Shader);

        Renderer::EndScene();
    }

    void OnEvent(Event &event) override
    {
        // To shut the compiler warning ups
        event;
    }

    void OnDearImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", m_SquareColor);
        ImGui::End();
    }

  private:
    std::shared_ptr<VertexArray> m_VertexArray;
    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<VertexArray> m_SquareVertexArray;
    std::shared_ptr<Shader> m_Shader2, m_TextureShader;
    std::shared_ptr<Texture2D> m_Texture;
    std::shared_ptr<Texture2D> m_LogoTexture;

    OrthographicCamera m_Camera;
    Vec3 m_CameraPos;

    f32 m_CameraVelocity{1.0f};

    Vec3 m_SquarePos;

    f32 m_SquareColor[3] = {0.2f, 0.3f, 0.8f};
};

class SandboxGame : public Application
{
  public:
    SandboxGame(const std::string_view &name, u32 width, u32 height)
    {
        // shut the warnings up
        name;
        width;
        height;
        PushLayer(std::make_unique<TestLayer>("TEST"));
    }
};

std::unique_ptr<Application> Terroir::CreateApplication()
{
    TERR_APP_INFO("Game Initialized!");
    return std::make_unique<SandboxGame>("Test", 1000, 1000);
}
