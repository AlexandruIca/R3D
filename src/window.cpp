#include <unordered_map>

#include <SDL.h>

#include "r3d/event.hpp"
#include "r3d/impl/log.hpp"
#include "r3d/window.hpp"

namespace r3d {

namespace {

class event_mapper
{
private:
    std::unordered_map<SDL_Keycode, r3d::key> m_key_mapper;

    event_mapper()
    {
        m_key_mapper.emplace(SDLK_a, r3d::key::key_a);
        m_key_mapper.emplace(SDLK_b, r3d::key::key_b);
        m_key_mapper.emplace(SDLK_c, r3d::key::key_c);
        m_key_mapper.emplace(SDLK_d, r3d::key::key_d);
        m_key_mapper.emplace(SDLK_e, r3d::key::key_e);
        m_key_mapper.emplace(SDLK_f, r3d::key::key_f);
        m_key_mapper.emplace(SDLK_g, r3d::key::key_g);
        m_key_mapper.emplace(SDLK_h, r3d::key::key_h);
        m_key_mapper.emplace(SDLK_i, r3d::key::key_i);
        m_key_mapper.emplace(SDLK_j, r3d::key::key_j);
        m_key_mapper.emplace(SDLK_k, r3d::key::key_k);
        m_key_mapper.emplace(SDLK_l, r3d::key::key_l);
        m_key_mapper.emplace(SDLK_m, r3d::key::key_m);
        m_key_mapper.emplace(SDLK_n, r3d::key::key_n);
        m_key_mapper.emplace(SDLK_o, r3d::key::key_o);
        m_key_mapper.emplace(SDLK_p, r3d::key::key_p);
        m_key_mapper.emplace(SDLK_q, r3d::key::key_q);
        m_key_mapper.emplace(SDLK_r, r3d::key::key_r);
        m_key_mapper.emplace(SDLK_s, r3d::key::key_s);
        m_key_mapper.emplace(SDLK_t, r3d::key::key_t);
        m_key_mapper.emplace(SDLK_u, r3d::key::key_u);
        m_key_mapper.emplace(SDLK_v, r3d::key::key_v);
        m_key_mapper.emplace(SDLK_w, r3d::key::key_w);
        m_key_mapper.emplace(SDLK_x, r3d::key::key_x);
        m_key_mapper.emplace(SDLK_y, r3d::key::key_y);
        m_key_mapper.emplace(SDLK_z, r3d::key::key_z);
        m_key_mapper.emplace(SDLK_UP, r3d::key::key_up);
        m_key_mapper.emplace(SDLK_DOWN, r3d::key::key_down);
        m_key_mapper.emplace(SDLK_LEFT, r3d::key::key_left);
        m_key_mapper.emplace(SDLK_RIGHT, r3d::key::key_right);
        m_key_mapper.emplace(SDLK_ESCAPE, r3d::key::key_esc);
    }

public:
    event_mapper(event_mapper const&) = delete;
    event_mapper(event_mapper&&) = delete;
    ~event_mapper() noexcept = default;

    auto operator=(event_mapper const&) = delete;
    auto operator=(event_mapper&&) = delete;

    static auto get() -> event_mapper&
    {
        static event_mapper m;
        return m;
    }

    [[nodiscard]] static auto get_key(SDL_Keycode const k) -> r3d::key
    {
        auto& inst = event_mapper::get();

        if(inst.m_key_mapper.find(k) == inst.m_key_mapper.end()) {
            return r3d::key::key_none;
        }

        return inst.m_key_mapper[k];
    }
};

} // namespace

window::window(std::string const& title, int const w, int const h)
    : m_window{ (SDL_Init(SDL_INIT_VIDEO),
                 SDL_CreateWindow(
                     title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_RESIZABLE)),
                [](SDL_Window* w) noexcept -> void {
                    SDL_DestroyWindow(w);
                    SDL_Quit();
                } }
    , m_width{ w }
    , m_height{ h }
    , m_closed{ false }
{
    if(m_window == nullptr) {
        ERROR("Could not create SDL_Window: {}!", SDL_GetError());
    }
}

window::window()
    : window{ "R3D", window::m_default_width, window::m_default_height }
{
}

auto window::get_mouse_coords() const noexcept -> std::pair<int, int>
{
    std::pair<int, int> coords{ 0, 0 };

    SDL_GetMouseState(&coords.first, &coords.second);

    return coords;
}

auto window::set_event_handler(std::function<void(r3d::event const&)> fun) -> void
{
    m_event_handler = std::move(fun);
}

auto window::handle_events() -> void
{
    SDL_Event ev;

    while(static_cast<bool>(SDL_PollEvent(&ev))) {
        switch(ev.type) {
        case SDL_QUIT: {
            m_closed = true;
            break;
        }
        case SDL_KEYDOWN: {
            auto const k = event_mapper::get_key(ev.key.keysym.sym);
            event e{ event_type::key_pressed, k };
            m_event_handler(e);

            break;
        }
        case SDL_KEYUP: {
            auto const k = event_mapper::get_key(ev.key.keysym.sym);
            event e{ event_type::key_released, k };
            m_event_handler(e);

            break;
        }
        case SDL_MOUSEBUTTONDOWN: {
            mouse_button b{ mouse_button::none };

            switch(ev.button.button) {
            case SDL_BUTTON_LEFT: {
                b = mouse_button::left;
                break;
            }
            case SDL_BUTTON_RIGHT: {
                b = mouse_button::right;
                break;
            }
            default: {
                break;
            }
            }

            event e{ event_type::mouse_button_pressed, b };
            m_event_handler(e);

            break;
        }
        case SDL_MOUSEBUTTONUP: {
            mouse_button b{ mouse_button::none };

            switch(ev.button.button) {
            case SDL_BUTTON_LEFT: {
                b = mouse_button::left;
                break;
            }
            case SDL_BUTTON_RIGHT: {
                b = mouse_button::right;
                break;
            }
            default: {
                break;
            }
            }

            event e{ event_type::mouse_button_released, b };
            m_event_handler(e);

            break;
        }
        case SDL_WINDOWEVENT: {
            switch(ev.window.event) {
            case SDL_WINDOWEVENT_SIZE_CHANGED: {
                m_width = ev.window.data1;
                m_height = ev.window.data2;

                LOG("Window resized to {}x{}!", m_width, m_height);
                event e{ event_type::window_size_changed };
                m_event_handler(e);

                break;
            }
            default: {
                break;
            }
            }
            break;
        }
        default: {
            break;
        }
        }
    }
}

auto window::get_sdl_window() noexcept -> SDL_Window*
{
    return m_window.get();
}

} // namespace r3d
