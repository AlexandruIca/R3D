#include <SDL.h>

#include "r3d/tick.hpp"

namespace r3d {

auto get_ticks() noexcept -> std::uint32_t
{
    return SDL_GetTicks();
}

} // namespace r3d
