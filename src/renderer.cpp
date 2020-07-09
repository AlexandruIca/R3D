#include <algorithm>

#include <SDL.h>

#include "r3d/impl/log.hpp"
#include "r3d/renderer.hpp"

namespace r3d {

namespace {

[[nodiscard]] auto point_inside_triangle(vec3f const& point, vec3f const& a, vec3f const& b, vec3f const& c) noexcept
    -> bool
{
    auto normal = cross(b - a, c - a);
    auto const main_triangle_area = normal.length();

    // Barycentric coordinates.
    // Find u, v, w (real numbers) so that u + v + w = 1, 0 <= u, v, w <= 1.
    // Let A = a, B = b, C = c, P = point.
    // Then u is Area(CAP) / Area(ABC), v is Area(ABP) / Area(ABC), w=1-u-v
    // If any of u,v,w is > 1 or < 0 return false, otherwise true.
    // The area of a triangle is calculated using the cross product(normally it
    // is the length of the cross product <b>divided by 2</b> but we are not
    // dividing by 2 here because the area of the main triangle is also
    // divided by 2 and it simplifies.
    auto const norm1 = cross(b - a, point - a);
    auto const u = norm1.length() / main_triangle_area;

    if(dot(normal, norm1) < 0) {
        return false;
    }

    auto const norm2 = cross(c - b, point - b);
    auto const v = norm2.length() / main_triangle_area;

    if(dot(normal, norm2) < 0) {
        return false;
    }

    auto const w = 1.0F - u - v;

    return !(w < 0 || w > 1);
}

} // namespace

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

auto renderer::draw_triangle(vec2i const& a, vec2i const& b, vec2i const& c, color const& col) -> void
{
    SDL_SetRenderDrawColor(m_renderer.get(), col.r, col.g, col.b, col.a);
    SDL_RenderDrawLine(m_renderer.get(), a[0], a[1], b[0], b[1]);
    SDL_RenderDrawLine(m_renderer.get(), b[0], b[1], c[0], c[1]);
    SDL_RenderDrawLine(m_renderer.get(), c[0], c[1], a[0], a[1]);
}

auto renderer::fill_triangle(vec2i const& a, vec2i const& b, vec2i const& c, color const& col, r3d::window const& wnd)
    -> void
{
    using arr2i = std::array<int, 2>;
    using arr3f = std::array<float, 3>;

    SDL_SetRenderDrawColor(m_renderer.get(), col.r, col.g, col.b, col.a);

    int const w = wnd.get_width() - 1;
    int const h = wnd.get_height() - 1;

    vec2i bbox_min{ arr2i{ w, h } };
    vec2i bbox_max{ 0 };

    bbox_min[0] = std::max(0, std::min({ bbox_min[0], a[0], b[0], c[0] }));
    bbox_min[1] = std::max(0, std::min({ bbox_min[1], a[1], b[1], c[1] }));

    bbox_max[0] = std::min(w, std::max({ bbox_max[0], a[0], b[0], c[0] }));
    bbox_max[1] = std::min(h, std::max({ bbox_max[1], a[1], b[1], c[1] }));

    vec2i point{ 0 };

    for(point[0] = bbox_min[0]; point[0] <= bbox_max[0]; ++point[0]) {
        for(point[1] = bbox_min[1]; point[1] <= bbox_max[1]; ++point[1]) {
            vec3f p1{ arr3f{ static_cast<float>(point[0]), static_cast<float>(point[1]), 1.0F } };
            vec3f p2{ arr3f{ static_cast<float>(a[0]), static_cast<float>(a[1]), 1.0F } };
            vec3f p3{ arr3f{ static_cast<float>(b[0]), static_cast<float>(b[1]), 1.0F } };
            vec3f p4{ arr3f{ static_cast<float>(c[0]), static_cast<float>(c[1]), 1.0F } };

            if(point_inside_triangle(p1, p2, p3, p4)) {
                SDL_RenderDrawPoint(m_renderer.get(), point[0], point[1]);
            }
        }
    }
}

auto test() -> void
{
    LOG("Hello {}!", "there");

    SDL_Init(SDL_INIT_VIDEO);
}

} // namespace r3d
