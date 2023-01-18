//
// Created by cjp on 1/3/23.
//

#include <Terroir.h>
#include <imgui.h>
#include <memory>

class TestLayer : public Terroir::Layer
{
  public:
    explicit TestLayer(const std::string &name) : Layer(name), m_Camera(-1.f, 1.f, -1.f, 1.f), m_CameraPos(0.0f)

    {
        std::array<f32, 3 * 7> vertices{-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f, -0.5f, 0.0f, 0.0f,
                                        1.0f,  0.0f,  1.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  1.0f};
        std::array<u32, 3> indices{0, 1, 2};

        m_VertexArray = std::shared_ptr<Terroir::VertexArray>(Terroir::VertexArray::Create());
        auto vertexBuffer =
            std::shared_ptr<Terroir::VertexBuffer>(Terroir::VertexBuffer::Create(&vertices[0], sizeof(vertices)));

        Terroir::BufferLayout layout{{"a_Pos", Terroir::ShaderDataType::Vec3},
                                     {"a_Color", Terroir::ShaderDataType::Vec4}};
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        auto indexBuffer =
            std::shared_ptr<Terroir::IndexBuffer>(Terroir::IndexBuffer::Create(&indices[0], indices.size()));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        vertexBuffer->Unbind();
        m_VertexArray->Unbind();

        std::string vertexSrc{R"(
    #version 330 core

    layout(location = 0) in vec3 a_Pos;
    layout(location = 1) in vec4 a_Color;


    out vec4 ourColor;
    out vec3 ourPos;

    uniform mat4 u_ViewProjection;

    void main()
    {
    ourPos = a_Pos;
    ourColor = a_Color;
    gl_Position = u_ViewProjection * vec4(a_Pos, 1.0);
    }
  )"};

        std::string fragSrc{R"(
    #version 330 core

    layout(location = 0) out vec4 FragColor;
    in vec4 ourColor;
    in vec3 ourPos;

    void main()
    {
    FragColor = vec4(ourPos * 0.5 + 0.5, 1.0);
    FragColor = ourColor;
    }
  )"};
        m_SquareVertexArray = std::shared_ptr<Terroir::VertexArray>(Terroir::VertexArray::Create());

        m_Shader = std::make_shared<Terroir::Shader>(vertexSrc, fragSrc);
        std::array<f32, 3 * 4> vertices2{-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f, -0.5f, 0.5f, 0.0f};
        std::shared_ptr<Terroir::VertexBuffer> squareBufferArray{
            std::shared_ptr<Terroir::VertexBuffer>(Terroir::VertexBuffer::Create(&vertices2[0], sizeof(vertices2)))};
        squareBufferArray->SetLayout({{"a_Pos", Terroir::ShaderDataType::Vec3}});
        m_SquareVertexArray->AddVertexBuffer(squareBufferArray);

        std::array<u32, 6> indices2{0, 1, 2, 2, 3, 0};
        std::shared_ptr<Terroir::IndexBuffer> ib2{
            std::shared_ptr<Terroir::IndexBuffer>(Terroir::IndexBuffer::Create(&indices2[0], indices2.size()))};
        m_SquareVertexArray->SetIndexBuffer(ib2);

        std::string vertexSrc2{R"(
    #version 330 core

    layout(location = 0) in vec3 a_Pos;

    uniform mat4 u_ViewProjection;

    out vec3 ourPos;

    void main()
    {
      ourPos = a_Pos;
      gl_Position = u_ViewProjection * vec4(a_Pos, 1.0);
    }
  )"};

        std::string fragSrc2{R"(
    #version 330 core

    out vec4 FragColor;
    in vec3 ourPos;

    void main()
    {
    FragColor = vec4(ourPos, 1.0);
    }
  )"};

        m_Shader2 = std::make_shared<Terroir::Shader>(vertexSrc2, fragSrc2);
    }

    ~TestLayer() override
    {
        TERR_APP_DEBUG("DELETING LAYER");
    }

    void OnUpdate() override
    {
        // NOLINTBEGIN(cppcoreguidelines-pro-type-union-access)
        if (Terroir::Input::IsKeyPressed(TERR_KEY_LEFT))
        {
            m_CameraPos.x -= m_CameraVelocity;
        }

        if (Terroir::Input::IsKeyPressed(TERR_KEY_RIGHT))
        {
            m_CameraPos.x += m_CameraVelocity;
        }

        if (Terroir::Input::IsKeyPressed(TERR_KEY_DOWN))
        {
            m_CameraPos.y -= m_CameraVelocity;
        }
        if (Terroir::Input::IsKeyPressed(TERR_KEY_UP))
        {
            m_CameraPos.y += m_CameraVelocity;
        }
        // NOLINTEND(cppcoreguidelines-pro-type-union-access)

        Terroir::RenderCommand::Clear({.2, .5, .4, 1});

        m_Camera.SetRotation(glfwGetTime() * 100.f);
        m_Camera.SetPosition(m_CameraPos);
        Terroir::Renderer::BeginScene(m_Camera);

        Terroir::Renderer::Submit(m_SquareVertexArray, m_Shader2);
        Terroir::Renderer::Submit(m_VertexArray, m_Shader);

        Terroir::Renderer::EndScene();
    }

    void OnEvent(Terroir::Event &event) override
    {
    }

    void OnDearImGuiRender() override
    {
        ImGui::Begin("test");
        ImGui::Text("Hello, Terroir!");
        ImGui::End();
    }

  private:
    std::shared_ptr<Terroir::VertexArray> m_VertexArray;
    std::shared_ptr<Terroir::Shader> m_Shader;
    std::shared_ptr<Terroir::VertexArray> m_SquareVertexArray;
    std::shared_ptr<Terroir::Shader> m_Shader2;

    Terroir::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPos;

    f32 m_CameraVelocity{0.1f};
};

class SandboxGame : public Terroir::Application
{
  public:
    SandboxGame()
    {
        PushLayer(std::make_unique<TestLayer>("TEST"));
    }
};

std::unique_ptr<Terroir::Application> Terroir::CreateApplication()
{
    TERR_APP_INFO("Game Initialized!");
    return std::make_unique<SandboxGame>();
}
