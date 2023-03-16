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

#ifndef TERROIR_ASSERT_H
#define TERROIR_ASSERT_H

#include "Terroir/src/log/Log.h"

#ifdef TERR_ENABLE_ASSERTS
#define TERR_ENGINE_ASSERT(x, ...)                                                                                     \
    {                                                                                                                  \
        if (!(x))                                                                                                      \
        {                                                                                                              \
            TERR_ENGINE_ERROR("Assertion Failed: {}", __VA_ARGS__);                                                    \
        }                                                                                                              \
    }
#define TERR_ASSERT(x, ...)                                                                                            \
    {                                                                                                                  \
        if (!(x))                                                                                                      \
        {                                                                                                              \
            TERR_APP_ERROR("Assertion Failed: {}", __VA_ARGS__);                                                       \
        }                                                                                                              \
    }
#else
#define TERR_ENGINE_ASSERT(x, ...)
#define TERR_ASSERT(x, ...)
#endif
#endif // TERROIR_ASSERT_H
