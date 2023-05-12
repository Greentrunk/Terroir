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

#ifndef TERROIR_H_MAAudioManager
#define TERROIR_H_MAAudioManager

#include "AudioManager.h"

#include "MiniAudio.h"
#include <filesystem>
#include <string>
#include <vector>

namespace Terroir
{

// Class the wraps around the high level MiniAudio api
class MAAudioManager : public AudioManager
{
  public:
    MAAudioManager();

    ~MAAudioManager() override;

    void Add(const std::string &, const std::filesystem::path &) override;
    void Play(const std::string &) override;

    // abstract method to cleanup ma_sounds at end of file
    void Cleanup() override;

  private:
    bool Exists(const std::string &) const;

    // Audio Engine
    std::unique_ptr<ma_engine> m_Engine;

    // List of ma_sounds may be own class in future | owns the respective ma_sounds
    std::vector<std::unique_ptr<ma_sound>> m_Sounds;
};

} // namespace Terroir

#endif