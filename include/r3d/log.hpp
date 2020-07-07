#ifndef LOG_HPP
#define LOG_HPP
#pragma once

#include <spdlog/spdlog.h>

#ifdef R3D_DEBUG
#define LOG(...) spdlog::info(__VA_ARGS__)
#elif defined(R3D_RELEASE)
#define LOG(...) static_cast<void>(0)
#endif

#endif // !LOG_HPP
