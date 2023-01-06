//
// Created by cjp on 1/6/23.
//

#ifndef TERROIR_ASSERT_H
#define TERROIR_ASSERT_H

#include "Terroir/pch/Tpch.h"

#ifdef TERR_ENABLE_ASSERTS
#define TERR_ENGINE_ASSERT(x, ...) {if(!(x)) {TERR_ENGINE_ERROR("Assertion Failed: {}", __VA_ARGS__); }}
#define TERR_ASSERT(x, ...) {if(!(x)) {TERR_APP_ERROR("Assertion Failed: {}", __VA_ARGS__); }}
#else
#define TERR_ENGINE_ASSERT(x, ...)
#define TERR_ASSERT(x, ...)
#endif
#endif //TERROIR_ASSERT_H
