#ifndef R3D_COLOR_HPP
#define R3D_COLOR_HPP
#pragma once

#include <cstdint>

namespace r3d {

struct color
{
    std::uint8_t r{ 0 };
    std::uint8_t g{ 0 };
    std::uint8_t b{ 0 };
    std::uint8_t a{ 0 };
};

} // namespace r3d

#endif // !R3D_COLOR_HPP
