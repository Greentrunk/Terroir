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

#ifndef TERROIR_COLOR_H
#define TERROIR_COLOR_H
#include "Terroir/src/math/Math.h"

namespace Terroir::Color
{
//TODO
// Soon to be Color library wrapper around a hashmap

// Vec4s of common colors
constexpr const Vec4 BLACK{0.0f, 0.0f, 0.0f, 1.0f};
constexpr const Vec4 WHITE{1.0f, 1.0f, 1.0f, 1.0f};
constexpr const Vec4 RED{1.0f, 0.0f, 0.0f, 1.0f};
constexpr const Vec4 GREEN{0.0f, 1.0f, 0.0f, 1.0f};
constexpr const Vec4 BLUE{0.0f, 0.0f, 1.0f, 1.0f};
constexpr const Vec4 YELLOW{1.0f, 1.0f, 0.0f, 1.0f};
constexpr const Vec4 PURPLE{1.0f, 0.0f, 1.0f, 1.0f};
constexpr const Vec4 CYAN{0.0f, 1.0f, 1.0f, 1.0f};
constexpr const Vec4 ORANGE{1.0f, 0.5f, 0.0f, 1.0f};
constexpr const Vec4 PINK{1.0f, 0.0f, 0.5f, 1.0f};
constexpr const Vec4 BROWN{0.5f, 0.25f, 0.0f, 1.0f};
constexpr const Vec4 GRAY{0.5f, 0.5f, 0.5f, 1.0f};
constexpr const Vec4 DARK_GRAY{0.25f, 0.25f, 0.25f, 1.0f};
constexpr const Vec4 LIGHT_GRAY{0.75f, 0.75f, 0.75f, 1.0f};
constexpr const Vec4 TRANSPARENT{0.0f, 0.0f, 0.0f, 0.0f};
} // namespace Terroir::Color

#endif // TERROIR_COLOR_H
