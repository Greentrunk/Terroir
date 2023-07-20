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

#include "FighterLike/FighterLike.h"
#include "Sandbox2D.h"
#include "pong/Pong.h"
#include <Terroir/src/core/AppEntry.h>

using namespace Terroir;

class SandboxGame : public Application
{
  public:
    SandboxGame(const std::string_view &name, u32 width, u32 height) : Application(name, width, height)
    {
        // PushLayer(std::make_unique<Sandbox2D>("2D")); // Your app
        // PushLayer(std::make_unique<Pong>("Pong")); // Pong example
        PushLayer(std::make_unique<FighterLike>("FighterLike")); // FighterLike example
    }
};

std::unique_ptr<Application> Terroir::CreateApplication()
{
    TERR_APP_INFO("Game Initialized!");
    return std::make_unique<SandboxGame>("Test", 1280, 720);
}
