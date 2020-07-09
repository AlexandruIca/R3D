#ifndef R3D_TICK_HPP
#define R3D_TICK_HPP
#pragma once

#include <cstdint>

namespace r3d {

[[nodiscard]] auto get_ticks() noexcept -> std::uint32_t;

} // namespace r3d

#endif // !R3D_TICK_HPP
