#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "r3d/renderer.hpp"

TEST_CASE("[Renderer] Basic")
{
    r3d::window wnd{};
    r3d::renderer rnd{ wnd };

    wnd.set_event_handler([&wnd](r3d::event const& ev) -> void {
        switch(ev.type()) {
        case r3d::event_type::key_pressed: {
            if(ev.get_key() == r3d::key::key_esc) {
                wnd.request_close();
            }
            else if(ev.get_key() == r3d::key::key_a) {
                MESSAGE("Pressed 'A'");
            }
            else {
                MESSAGE("Key pressed");
            }
            break;
        }
        case r3d::event_type::key_released: {
            if(ev.get_key() == r3d::key::key_a) {
                MESSAGE("Released 'A'");
            }
            else {
                MESSAGE("Key released");
            }
            break;
        }
        case r3d::event_type::mouse_button_pressed: {
            auto const [x, y] = wnd.get_mouse_coords();

            if(ev.get_mouse_button() == r3d::mouse_button::left) {
                MESSAGE("Left click at " << x << ", " << y);
            }
            else if(ev.get_mouse_button() == r3d::mouse_button::right) {
                MESSAGE("Right click at " << x << ", " << y);
            }
            break;
        }
        case r3d::event_type::mouse_button_released: {
            auto const [x, y] = wnd.get_mouse_coords();

            if(ev.get_mouse_button() == r3d::mouse_button::left) {
                MESSAGE("Left click released at " << x << ", " << y);
            }
            else if(ev.get_mouse_button() == r3d::mouse_button::right) {
                MESSAGE("Right click released at " << x << ", " << y);
            }
            break;
        }
        default: {
            break;
        }
        }
    });

    constexpr r3d::color c{ 255, 107, 128, 255 };
    constexpr int center_offset = 10;

    while(!wnd.closed()) {
        wnd.handle_events();
        rnd.clear();

        auto const [w, h] = wnd.get_dimensions();
        auto const center_x = w / 2;
        auto const center_y = h / 2;

        for(int i = center_x - center_offset; i <= center_x + center_offset; ++i) {
            rnd.draw_point(i, center_y, c);
        }

        rnd.update();
    }
}
