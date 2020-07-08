#include <SDL.h>

#include "r3d/impl/log.hpp"
#include "r3d/renderer.hpp"

namespace r3d {

renderer::renderer(window& wnd)
    : m_renderer{ SDL_CreateRenderer(wnd.get_sdl_window(), -1, SDL_RENDERER_ACCELERATED),
                  [](SDL_Renderer* r) noexcept { SDL_DestroyRenderer(r); } }
{
    if(m_renderer == nullptr) {
        ERROR("Couldn't create the renderer: {}!", SDL_GetError());
    }
}

auto renderer::clear() noexcept -> void
{
    SDL_SetRenderDrawColor(m_renderer.get(), m_clear_color.r, m_clear_color.g, m_clear_color.b, m_clear_color.a);
    SDL_RenderClear(m_renderer.get());
}

auto renderer::update() noexcept -> void
{
    SDL_RenderPresent(m_renderer.get());
}

auto renderer::draw_point(int const x, int const y, color const c) -> void
{
    SDL_SetRenderDrawColor(m_renderer.get(), c.r, c.g, c.b, c.a);
    SDL_RenderDrawPoint(m_renderer.get(), x, y);
}

auto test() -> void
{
    LOG("Hello {}!", "there");

    SDL_Init(SDL_INIT_VIDEO);
}

} // namespace r3d
