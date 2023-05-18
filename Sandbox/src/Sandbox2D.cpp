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

#include "Sandbox2D.h"
#include "filesystem"
#include <imgui.h>

constexpr const auto SCREEN_WIDTH{1280.f};
constexpr const auto SCREEN_HEIGHT{720.f};
constexpr const auto SCREEN_TOP{SCREEN_HEIGHT / 2};
constexpr const auto SCREEN_BOTTOM{-SCREEN_HEIGHT / 2};
constexpr const auto SCREEN_LEFT{-SCREEN_WIDTH / 2};
constexpr const auto SCREEN_RIGHT{SCREEN_WIDTH / 2};
constexpr const f32 PADDLE_WIDTH{30.f};
constexpr const f32 PADDLE_HEIGHT{SCREEN_HEIGHT / 4};
constexpr const f32 HALF_PADDLE_Y{PADDLE_HEIGHT / 2};
auto humanPos{Vec2(SCREEN_LEFT + PADDLE_WIDTH, 0.f)};
constexpr auto paddleVelocity{800.0f};
constexpr const f32 BALL_SIDE = 20.f;
auto ballPos{Vec2{0.f, 0.f}};
auto cpuPos{Vec2(SCREEN_RIGHT - PADDLE_WIDTH, 0.f)};
auto ballVelocity{Vec2(-1000.f, -1000.f)};

// round number
auto roundNum{1};

// Scores
auto humanScore{0};
auto cpuScore{0};

// Reset round
void ResetRound()
{
    roundNum++;
    ballPos = Vec2(0.f, 0.f);
    // Check if round is even or odd
    if (roundNum % 2 == 0)
    {
        ballVelocity = Vec2(1000.f, 1000.f);
    }
    else
    {
        ballVelocity = Vec2(-1000.f, -1000.f);
    }
}

void MovePaddle(f32 dt, f32 velocity)
{
    auto &paddleY{humanPos.y};
    auto newPos{velocity * dt};
    if (Input::IsKeyPressed(TERR_KEY_W))
    {
        auto paddleTop{paddleY + newPos + HALF_PADDLE_Y};
        if (paddleTop >= SCREEN_TOP)
        {
            paddleY += 0;
        }
        else
        {
            paddleY += newPos;
        }
    }
    if (Input::IsKeyPressed(TERR_KEY_S))
    {
        auto paddleBottom{paddleY - newPos - HALF_PADDLE_Y};
        if (paddleBottom <= SCREEN_BOTTOM)
        {
            paddleY -= 0;
        }
        else
        {
            paddleY -= newPos;
        }
    }
}

// each frame, move the ball by the ball velocity and check for collisions
void MoveBall(f32 dt)
{

    // Grab audio manager
    auto &audioManager{Application::Get().GetAudioManager()};

    ballPos.x += ballVelocity.x * dt;
    ballPos.y += ballVelocity.y * dt;

    auto ballLeft{ballPos.x - BALL_SIDE / 2};
    auto ballRight{ballPos.x + BALL_SIDE / 2};
    auto ballTop{ballPos.y + BALL_SIDE / 2};
    auto ballBottom{ballPos.y - BALL_SIDE / 2};
    auto cpuPaddleY{cpuPos.y};
    auto humanPaddleY{humanPos.y};

    // Check colisions for walls
    if (ballPos.y >= SCREEN_TOP || ballPos.y <= SCREEN_BOTTOM)
    {
        ballVelocity.y = -ballVelocity.y;
    }

    // Check colisions for paddels
    if (ballLeft <= SCREEN_LEFT + PADDLE_WIDTH)
    {
        if (ballTop >= humanPaddleY - HALF_PADDLE_Y && ballBottom <= humanPaddleY + HALF_PADDLE_Y)
        {
            ballVelocity.x = -ballVelocity.x;
            audioManager.Play("bounce");
        }
        else
        {
            // CPU Scored
            cpuScore++;
            ResetRound();
        }
    }
    else if (ballRight >= SCREEN_RIGHT - PADDLE_WIDTH)
    {
        if (ballTop >= cpuPaddleY - HALF_PADDLE_Y && ballBottom <= cpuPaddleY + HALF_PADDLE_Y)
        {
            ballVelocity.x = -ballVelocity.x;
            audioManager.Play("bounce");
        }
        else
        {
            // Human Scored
            humanScore++;
            ResetRound();
        }
    }
}

// CPU Paddle AI impl
void CpuPaddleAI(f32 dt)
{
    if (ballPos.y < cpuPos.y)
    {
        cpuPos.y -= paddleVelocity * dt;
    }
    else if (ballPos.y > cpuPos.y)
    {
        cpuPos.y += paddleVelocity * dt;
    }
}

Sandbox2D::Sandbox2D(const std::string_view &name) : Layer(name)
{
    CreateCamera(Application::Get().GetWindowWidth(), Application::Get().GetWindowHeight());

    // // Register test sound
    auto &audioManager{Application::Get().GetAudioManager()};
    audioManager.Add("music", "Sandbox/assets/music.wav");
    audioManager.Add("bounce", "Sandbox/assets/bounce.wav");
}

void Sandbox2D::OnAttach()
{
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Timestep dt)
{
    TERR_PROFILE_FUNC;

    // Clear Screen to color
    RenderCommand::Clear(Color::BLACK);

    // Process input and update
    MovePaddle(dt, paddleVelocity);
    MoveBall(dt);
    CpuPaddleAI(dt);

    // Draw whatever you want
    Renderer2D::BeginScene(*m_Camera);

    // Middle of screen coords
    auto textPos{Vec3(-50.f, 0.0f, 1.0f)};
    auto humanScorePos{Vec3(-200.f, 200.0f, 1.0f)};
    auto cpuScorePos{Vec3(200.f, 200.0f, 1.0f)};
    const auto humanScoreStr{std::to_string(humanScore)};
    const auto cpuScoreStr{std::to_string(cpuScore)};
    // Text
    Renderer2D::DrawText("Pong", textPos, {1.f, 1.f}, Color::WHITE);
    Renderer2D::DrawText(humanScoreStr, humanScorePos ,{3.f, 3.f}, Color::WHITE);
    Renderer2D::DrawText(cpuScoreStr, cpuScorePos ,{3.f, 3.f}, Color::WHITE);

    // Ball
    Renderer2D::DrawRect(ballPos, {BALL_SIDE, BALL_SIDE}, Color::WHITE);

    // Paddles
    Renderer2D::DrawRect(humanPos, {PADDLE_WIDTH, PADDLE_HEIGHT}, Color::WHITE);
    Renderer2D::DrawRect(cpuPos, {PADDLE_WIDTH, PADDLE_HEIGHT}, Color::WHITE);

    Renderer2D::EndScene();
}
void Sandbox2D::OnDearImGuiRender()
{
    TERR_PROFILE_FUNC;
}

void Sandbox2D::OnEvent(Event &e)
{
}

void Sandbox2D::CreateCamera(u32 width, u32 height)
{
    auto aspectRatio{static_cast<f32>(width) / static_cast<f32>(height)};
    auto camHeight{Application::Get().GetWindowHeight() / 2};
    auto bottom{-static_cast<i32>(camHeight)};
    auto top{camHeight};
    auto left{static_cast<f32>(bottom) * aspectRatio};
    auto right{static_cast<f32>(top) * aspectRatio};
    m_Camera = std::make_unique<OrthographicCamera>(left, right, bottom, top);
}
