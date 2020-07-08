#ifndef R3D_WINDOW_HPP
#define R3D_WINDOW_HPP
#pragma once

#include <functional>
#include <memory>
#include <string>
#include <utility>

#include "r3d/event.hpp"

class SDL_Window;

namespace r3d {

class window
{
private:
    std::unique_ptr<SDL_Window, void (*)(SDL_Window*) noexcept> m_window;
    std::function<void(r3d::event const&)> m_event_handler;
    int m_width;
    int m_height;
    bool m_closed;

    static constexpr int m_default_width = 600;
    static constexpr int m_default_height = 400;

public:
    window();
    window(window const&) = delete;
    window(window&&) noexcept = default;
    ~window() noexcept = default;

    window(std::string const& title, int w, int h);

    auto operator=(window const&) -> window& = delete;
    auto operator=(window&&) noexcept -> window& = default;

    [[nodiscard]] auto get_mouse_coords() const noexcept -> std::pair<int, int>;

    [[nodiscard]] inline auto closed() const noexcept -> bool
    {
        return m_closed;
    }

    auto set_event_handler(std::function<void(r3d::event const&)> fun) -> void;
    auto handle_events() -> void;

    inline auto request_close() -> void
    {
        m_closed = true;
    }

    [[nodiscard]] auto get_sdl_window() noexcept -> SDL_Window*;

    [[nodiscard]] inline auto get_width() const noexcept -> int
    {
        return m_width;
    }
    [[nodiscard]] inline auto get_height() const noexcept -> int
    {
        return m_height;
    }
    [[nodiscard]] inline auto get_dimensions() const noexcept -> std::pair<int, int>
    {
        return { m_width, m_height };
    }
};

} // namespace r3d

#endif // !R3D_WINDOW_HPP
