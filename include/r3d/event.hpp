#ifndef R3D_EVENT_HPP
#define R3D_EVENT_HPP
#pragma once

namespace r3d {

enum class event_type
{
    key_pressed,
    key_released,
    mouse_button_pressed,
    mouse_button_released,
    window_size_changed,
    none
};

enum class key
{
    key_a,
    key_b,
    key_c,
    key_d,
    key_e,
    key_f,
    key_g,
    key_h,
    key_i,
    key_j,
    key_k,
    key_l,
    key_m,
    key_n,
    key_o,
    key_p,
    key_q,
    key_r,
    key_s,
    key_t,
    key_u,
    key_v,
    key_w,
    key_x,
    key_y,
    key_z,
    key_up,
    key_down,
    key_left,
    key_right,
    key_esc,
    key_none
};

enum class mouse_button
{
    left,
    right,
    none
};

class event
{
private:
    event_type m_type{ event_type::none };
    key m_key{ key::key_none };
    mouse_button m_mouse_button{ mouse_button::none };

public:
    event() noexcept = default;
    event(event const&) noexcept = default;
    event(event&&) noexcept = default;
    ~event() noexcept = default;

    explicit inline event(event_type type)
        : m_type{ type }
    {
    }
    inline event(event_type type, key k)
        : m_type{ type }
        , m_key{ k }
    {
    }
    inline event(event_type type, mouse_button b)
        : m_type{ type }
        , m_mouse_button{ b }
    {
    }

    auto operator=(event const&) noexcept -> event& = default;
    auto operator=(event&&) noexcept -> event& = default;

    [[nodiscard]] inline auto type() const noexcept -> event_type
    {
        return m_type;
    }

    [[nodiscard]] inline auto get_key() const noexcept -> key
    {
        return m_key;
    }

    [[nodiscard]] inline auto get_mouse_button() const noexcept -> mouse_button
    {
        return m_mouse_button;
    }
};

} // namespace r3d

#endif // !R3D_EVENT_HPP
