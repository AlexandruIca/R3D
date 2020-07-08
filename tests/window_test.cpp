#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "r3d/window.hpp"

TEST_CASE("[Window]")
{
    r3d::window wnd{};

    auto const [w, h] = wnd.get_dimensions();
    MESSAGE("Window dimensions: " << w << 'x' << h);

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

    while(!wnd.closed()) {
        wnd.handle_events();
    }
}
