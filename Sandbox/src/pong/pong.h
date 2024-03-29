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

#ifndef PONG 
#define PONG 

#include "Terroir.h"

using namespace Terroir;

class Pong : public Layer
{
  public:
    explicit Pong(const std::string_view &);
    ~Pong() override = default;
    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate(Timestep) override;
    void OnDearImGuiRender() override;
    void OnEvent(Event &) override;
    void CreateCamera(u32, u32);

  private:
    std::unique_ptr<OrthographicCamera> m_Camera;
};

#endif // PONG 