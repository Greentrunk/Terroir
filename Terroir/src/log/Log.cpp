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

#include "Log.h"

namespace Terroir
{
// Declare statics
std::shared_ptr<spdlog::logger> Log::sp_EngineLogger;
std::shared_ptr<spdlog::logger> Log::sp_ClientLogger;

// Setup spd sinks and config loggers
void Log::Init()
{
    auto engineSink{std::make_shared<spdlog::sinks::stdout_color_sink_mt>()};
    auto clientSink{std::make_shared<spdlog::sinks::stdout_color_sink_mt>()};
    auto pattern{"%^[%c] [%n] [%l] [%s:%#]: %v%$"};

    sp_EngineLogger = std::make_shared<spdlog::logger>("TERROIR", engineSink);
    sp_ClientLogger = std::make_shared<spdlog::logger>("APP", clientSink);

    sp_EngineLogger->set_level(spdlog::level::trace);
    sp_ClientLogger->set_level(spdlog::level::trace);

    sp_EngineLogger->set_pattern(pattern);
    sp_ClientLogger->set_pattern(pattern);
}
} // namespace Terroir
