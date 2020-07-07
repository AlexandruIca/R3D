#include <SDL.h>

#include "r3d/log.hpp"
#include "r3d/renderer.hpp"

namespace r3d {

auto test() -> void
{
    LOG("Hello {}!", "there");

    SDL_Init(SDL_INIT_VIDEO);
}

} // namespace r3d
