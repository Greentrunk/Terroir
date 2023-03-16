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

#ifndef TERROIR_PROFILE_H
#define TERROIR_PROFILE_H

// TRACY DEFINES
#ifdef TERR_ENABLE_PROFILING
#include <tracy/Tracy.hpp>
// #include <tracy/TracyOpenGL.hpp>
#define TERR_PROFILE ZoneScoped
#define TERR_PROFILE_FUNC ZoneScopedN(__FUNCTION__)
#define TERR_PROFILE_SCOPE(name) ZoneScopedN(name)
#define TERR_PROFILE_FRAME FrameMark
#define TERR_PROFILE_TAG(tag) ZoneText(tag, strlen(tag))
#define TERR_PROFILE_LOG(msg) TracyMessage(msg, strlen(msg))
#define TERR_PROFILE_VALUE(name, value) TracyPlot(name, value)
// Use with raw pointers
#define TERR_PROFILE_ALLOC(ptr, size) TracyAlloc(ptr, size)
#define TERR_PROFILE_FREE(ptr) TracyFree(ptr)
// To be used with smart pointers only
template <typename T>
concept SmartPointer = requires(T t) {
                           {
                               t.get()
                               } -> std::same_as<typename T::element_type *>;
                       };
template <SmartPointer T> constexpr void TERR_PROFILE_ALLOC_SMART(T &ptr)
{
    TracyAlloc(ptr.get(), sizeof(ptr));
}
template <SmartPointer T> constexpr void TERR_PROFILE_FREE_SMART(T &ptr)
{
    TracyFree(ptr.get());
}

// #define TERR_PROFILE_GPU_CTX TracyGpuContext
// #define TERR_PROFILE_GPU_ZONE(name) TracyGpuZone(name)
// #define TERR_PROFILE_GPU_ZONE_N(name, n) TracyGpuZoneN(name, n)
// #define TERR_PROFILE_GPU_Collect TracyGpuCollect
#else
#define TERR_PROFILE
#define TERR_PROFILE_FUNC
#define TERR_PROFILE_SCOPE(name)
#define TERR_PROFILE_FRAME
#define TERR_PROFILE_TAG(tag)
#define TERR_PROFILE_LOG(msg)
#define TERR_PROFILE_VALUE(name, value)
#define TERR_PROFILE_ALLOC(ptr, size)
#define TERR_PROFILE_FREE(ptr)
// #define TERR_PROFILE_ALLOC_SMART(ptr, type)
#define TERR_PROFILE_ALLOC_SMART(ptr)
#define TERR_PROFILE_FREE_SMART(ptr)
#define TERR_PROFILE_GPU_CTX
#define TERR_PROFILE_GPU_ZONE(name)
#define TERR_PROFILE_GPU_ZONE_N(name, n)
#define TERR_PROFILE_GPU_Collect
#endif // TERR_ENABLE_PROFILING
#endif // TERROIR_PROFILE_H
