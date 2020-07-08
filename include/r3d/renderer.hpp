#ifndef R3D_RENDERER_HPP
#define R3D_RENDERER_HPP
#pragma once

#include <memory>

class SDL_Renderer;

#include "r3d/color.hpp"
#include "r3d/window.hpp"

namespace r3d {

class renderer
{
private:
    std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*) noexcept> m_renderer;

    static constexpr color m_clear_color = color{ 0, 0, 0, 255 };

public:
    renderer() = delete;
    renderer(renderer const&) = delete;
    renderer(renderer&&) noexcept = default;
    ~renderer() noexcept = default;

    explicit renderer(window& wnd);

    auto operator=(renderer const&) = delete;
    auto operator=(renderer&&) = delete;

    auto clear() noexcept -> void;
    auto update() noexcept -> void;

    auto draw_point(int x, int y, color c) -> void;
};

auto test() -> void;

} // namespace r3d

#endif // !R3D_RENDERER_HPP
