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

#ifndef TERROIR_SANDBOX2D_H
#define TERROIR_SANDBOX2D_H

#include "Terroir.h"

using namespace Terroir;

class Sandbox2D : public Layer
{
  public:
    explicit Sandbox2D(const std::string_view &);
    ~Sandbox2D() override = default;
    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate(Timestep) override;
    void OnDearImGuiRender() override;
    void OnEvent(Event &) override;

  private:
    OrthographicCameraController m_CameraController;

    std::shared_ptr<Texture2D> m_GreenTrunkTexture;
};

#endif // TERROIR_SANDBOX2D_H
