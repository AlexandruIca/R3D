#ifndef R3D_LOG_HPP
#define R3D_LOG_HPP
#pragma once

#include <spdlog/spdlog.h>

#ifdef R3D_DEBUG

#define LOG(...) spdlog::info(__VA_ARGS__)
#define ERROR(...) spdlog::error(__VA_ARGS__)

#elif defined(R3D_RELEASE)

#define LOG(...) static_cast<void>(0)
#define ERROR(...) static_cast<void>(0)

#endif

#endif // !R3D_LOG_HPP
