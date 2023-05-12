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

#include "MAAudioManager.h"
#include "Tpch.h"
#include "core/Assert.h"

namespace Terroir
{
MAAudioManager::MAAudioManager() : m_Engine(std::make_unique<ma_engine>())
{
    ma_result result;

    // Create the audio engine
    result = ma_engine_init(nullptr, m_Engine.get());

    if (result != MA_SUCCESS)
    {
        TERR_ENGINE_ERROR("Failed to initialize audio engine: {}", result);
        return;
    }

    // Log success
    TERR_ENGINE_INFO("Successfully initialized audio engine");
}

MAAudioManager::~MAAudioManager()
{
    // Empty m_Sounds if still has sounds
    if (!m_Sounds.empty())
    {
        TERR_ENGINE_WARN("m_Sounds not empty on destruction");
        // Uninitialize all sounds in MiniAudio
        for (auto &sound : m_Sounds)
        {
            ma_sound_uninit(sound.get());
        }
        m_Sounds.clear();
    }

    // Uninitialize the audio engine
    ma_engine_uninit(m_Engine.get());

    // Profile free
    TERR_PROFILE_FREE_SMART(m_Engine);
}
void MAAudioManager::Add(const std::string &name, const std::filesystem::path &path)
{
    // Check if sound is in SoundLibrary
    TERR_ENGINE_ASSERT(!Exists(name), "Sound already exists in SoundLibrary");
    m_SoundLibrary[name] = path;
    // TERR_ENGINE_INFO("Sound {} added to SoundLibrary from path {}", name, path.string());
}

void MAAudioManager::Play(const std::string &name)
{
    // Check if sound is in SoundLibrary
    if (!Exists(name))
    {
        // Doesn't exist
        TERR_ENGINE_ERROR("Sound {} not found in SoundLibrary", name);
        return;
    }
    else
    {
        // Heap allocate new sound
        auto sound = std::make_unique<ma_sound>();

        const auto &soundPath = m_SoundLibrary[name].string();
        // TERR_ENGINE_INFO("Retrieved sound path: {}, c_str: {}", soundPath, soundPath.c_str());
        auto soundResult{ma_sound_init_from_file(m_Engine.get(), soundPath.c_str(),
                                                 MA_SOUND_FLAG_DECODE | MA_SOUND_FLAG_STREAM, nullptr, nullptr,
                                                 sound.get())};
        if (soundResult != MA_SUCCESS)
        {
            TERR_ENGINE_ERROR("Failed to load sound: {}", soundResult);
            return;
        }

        ma_sound_start(sound.get());

        // move sounds into m_Sounds
        m_Sounds.push_back(std::move(sound));
    }
}

void MAAudioManager::Cleanup()
{
    // Loop through m_Sounds and check if they are at the end
    for (auto &sound : m_Sounds)
    {
        if (ma_sound_at_end(sound.get()))
        {
            // Uninitialize sound
            ma_sound_uninit(sound.get());
            // Remove sound from m_Sounds
            const auto [ret, last] =
                std::ranges::remove_if(m_Sounds, [&sound](const auto &s) { return s.get() == sound.get(); });
            if (ret != m_Sounds.end())
            {
                m_Sounds.erase(ret, last);
            }
        }
    }
}

bool MAAudioManager::Exists(const std::string &name) const
{
    return m_SoundLibrary.find(name) != m_SoundLibrary.end();
}
} // namespace Terroir