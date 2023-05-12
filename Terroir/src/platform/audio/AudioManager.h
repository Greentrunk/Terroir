// ///////////////////////////////////////////////////////////////////////////
//  Copyright (c) Christopher J. Pohl 2023 to Present.  All Rights Reserved.
//
//  This file is part of TERROIR ENGINE:
//  This is free software as described by the Apache 2.0 License
//
//  The above copyright notice shall be included in all portions of this software
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
//  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
//  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// ///////////////////////////////////////////////////////////////////////////

#ifndef TERROIR_AUDIOMANAGER_H
#define TERROIR_AUDIOMANAGER_H

namespace Terroir
{

struct AudioManagerProperties
{
};

class AudioManager
{
  public:
    AudioManager() = default;
    virtual ~AudioManager() = default;

    virtual void Add(const std::string &, const std::filesystem::path &) = 0;
    virtual void Play(const std::string &) = 0;

    // abstract method to cleanup sounds at end of file
    virtual void Cleanup() = 0;

    // Create new audiomanager by platform
    static std::unique_ptr<AudioManager> Create(const AudioManagerProperties &);

    // SoundLibrary
  protected:
    std::unordered_map<std::string, std::filesystem::path> m_SoundLibrary{};
};

} // namespace Terroir

#endif // TERROIR_AUDIOMANAGER_H
