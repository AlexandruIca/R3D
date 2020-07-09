#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <cmath>
#include <vector>

#include "r3d/renderer.hpp"
#include "r3d/tick.hpp"
#include "r3d/vec.hpp"

TEST_CASE("[SimplePerspectiveCube]")
{
    using arr3f = std::array<float, 3>;

    r3d::window wnd{};
    r3d::renderer rnd{ wnd };

    std::vector<r3d::triangle> mesh = { // SOUTH
                                        { r3d::vec3f{ arr3f{ 0.0F, 0.0F, 0.0F } },
                                          r3d::vec3f{ arr3f{ 0.0F, 1.0F, 0.0F } },
                                          r3d::vec3f{ arr3f{ 1.0F, 1.0F, 0.0F } } },
                                        { r3d::vec3f{ arr3f{ 0.0F, 0.0F, 0.0F } },
                                          r3d::vec3f{ arr3f{ 1.0F, 1.0F, 0.0F } },
                                          r3d::vec3f{ arr3f{ 1.0F, 0.0F, 0.0F } } },
                                        // EAST
                                        { r3d::vec3f{ arr3f{ 1.0F, 0.0F, 0.0F } },
                                          r3d::vec3f{ arr3f{ 1.0F, 1.0F, 0.0F } },
                                          r3d::vec3f{ arr3f{ 1.0F, 1.0F, 1.0F } } },
                                        { r3d::vec3f{ arr3f{ 1.0F, 0.0F, 0.0F } },
                                          r3d::vec3f{ arr3f{ 1.0F, 1.0F, 1.0F } },
                                          r3d::vec3f{ arr3f{ 1.0F, 0.0F, 1.0F } } },
                                        // NORTH
                                        { r3d::vec3f{ arr3f{ 1.0F, 0.0F, 1.0F } },
                                          r3d::vec3f{ arr3f{ 1.0F, 1.0F, 1.0F } },
                                          r3d::vec3f{ arr3f{ 0.0F, 1.0F, 1.0F } } },
                                        { r3d::vec3f{ arr3f{ 1.0F, 0.0F, 1.0F } },
                                          r3d::vec3f{ arr3f{ 0.0F, 1.0F, 1.0F } },
                                          r3d::vec3f{ arr3f{ 0.0F, 0.0F, 1.0F } } },
                                        // WEST
                                        { r3d::vec3f{ arr3f{ 0.0F, 0.0F, 1.0F } },
                                          r3d::vec3f{ arr3f{ 0.0F, 1.0F, 1.0F } },
                                          r3d::vec3f{ arr3f{ 0.0F, 1.0F, 0.0F } } },
                                        { r3d::vec3f{ arr3f{ 0.0F, 0.0F, 1.0F } },
                                          r3d::vec3f{ arr3f{ 0.0F, 1.0F, 0.0F } },
                                          r3d::vec3f{ arr3f{ 0.0F, 0.0F, 0.0F } } },
                                        // TOP
                                        { r3d::vec3f{ arr3f{ 0.0F, 1.0F, 0.0F } },
                                          r3d::vec3f{ arr3f{ 0.0F, 1.0F, 1.0F } },
                                          r3d::vec3f{ arr3f{ 1.0F, 1.0F, 1.0F } } },
                                        { r3d::vec3f{ arr3f{ 0.0F, 1.0F, 0.0F } },
                                          r3d::vec3f{ arr3f{ 1.0F, 1.0F, 1.0F } },
                                          r3d::vec3f{ arr3f{ 1.0F, 1.0F, 0.0F } } },
                                        // BOTTOM
                                        { r3d::vec3f{ arr3f{ 1.0F, 0.0F, 1.0F } },
                                          r3d::vec3f{ arr3f{ 0.0F, 0.0F, 1.0F } },
                                          r3d::vec3f{ arr3f{ 0.0F, 0.0F, 0.0F } } },
                                        { r3d::vec3f{ arr3f{ 1.0F, 0.0F, 1.0F } },
                                          r3d::vec3f{ arr3f{ 0.0F, 0.0F, 0.0F } },
                                          r3d::vec3f{ arr3f{ 1.0F, 0.0F, 0.0F } } }
    };

    constexpr float pi = 3.14159265F;
    constexpr float near = 0.1F;
    constexpr float far = 1000.0F;
    constexpr float fov = 90.0F;
    const float fov_rad = 1 / std::tan(fov * 0.5F / 180 * pi);

    r3d::mat4f projection_matrix{ 0.0F };

    projection_matrix(0, 0) = static_cast<float>(wnd.get_height()) / static_cast<float>(wnd.get_width()) * fov_rad;
    projection_matrix(1, 1) = fov_rad;
    projection_matrix(2, 2) = far / (far - near);
    projection_matrix(2, 3) = 1.0F;
    projection_matrix(3, 2) = (-far * near) / (far - near);

    wnd.set_event_handler([&wnd, &projection_matrix, fov_rad](r3d::event const& e) -> void {
        if(e.type() == r3d::event_type::key_pressed && e.get_key() == r3d::key::key_esc) {
            wnd.request_close();
        }
        else if(e.type() == r3d::event_type::window_size_changed) {
            // change aspect ratio
            projection_matrix(0, 0) =
                static_cast<float>(wnd.get_height()) / static_cast<float>(wnd.get_width()) * fov_rad;
            MESSAGE("Window size changed");
        }
    });

    using namespace r3d::operators;
    constexpr r3d::color white{ 255, 255, 255, 255 };
    constexpr float translate_offset = 3.0F;

    float rotation_angle{ 0.0F };

    r3d::vec3f camera{ 0.0F };

    r3d::mat4f rot_z{ 0.0F };
    r3d::mat4f rot_x{ 0.0F };

    rot_z(2, 2) = 1.0F;
    rot_z(3, 3) = 1.0F;

    rot_x(0, 0) = 1.0F;
    rot_x(3, 3) = 1.0F;

    while(!wnd.closed()) {
        using namespace std::chrono;

        wnd.handle_events();
        rnd.clear();

        rotation_angle = static_cast<float>(r3d::get_ticks()) / 1000.0F; // NOLINT

        rot_z(0, 0) = std::cos(rotation_angle);
        rot_z(0, 1) = std::sin(rotation_angle);
        rot_z(1, 0) = -std::sin(rotation_angle);
        rot_z(1, 1) = std::cos(rotation_angle);

        rot_x(1, 1) = std::cos(rotation_angle * 0.5F);  // NOLINT
        rot_x(1, 2) = std::sin(rotation_angle * 0.5F);  // NOLINT
        rot_x(2, 1) = -std::sin(rotation_angle * 0.5F); // NOLINT
        rot_x(2, 2) = std::cos(rotation_angle * 0.5F);  // NOLINT

        for(auto const& tri : mesh) {
            r3d::triangle projected{};
            r3d::triangle tri_translated{};
            r3d::triangle tri_rot_z{};
            r3d::triangle tri_rot_x{};

            tri_rot_z[0] = tri[0] * rot_z;
            tri_rot_z[1] = tri[1] * rot_z;
            tri_rot_z[2] = tri[2] * rot_z;

            tri_rot_x[0] = tri_rot_z[0] * rot_x;
            tri_rot_x[1] = tri_rot_z[1] * rot_x;
            tri_rot_x[2] = tri_rot_z[2] * rot_x;

            tri_translated = tri_rot_x;

            tri_translated[0][2] = tri_rot_x[0][2] + translate_offset;
            tri_translated[1][2] = tri_rot_x[1][2] + translate_offset;
            tri_translated[2][2] = tri_rot_x[2][2] + translate_offset;

            r3d::vec3f normal{ 0.0F };
            r3d::vec3f line1{ 0.0F };
            r3d::vec3f line2{ 0.0F };

            line1 = tri_translated[1] - tri_translated[0];
            line2 = tri_translated[2] - tri_translated[0];
            normal = r3d::cross(line1, line2);
            normal.normalize();

            // if(normal[2] < 0) {
            if(r3d::dot(normal, tri_translated[0] - camera) < 0.0F) {
                projected[0] = tri_translated[0] * projection_matrix;
                projected[1] = tri_translated[1] * projection_matrix;
                projected[2] = tri_translated[2] * projection_matrix;

                for(std::size_t i = 0; i < 3; ++i) {
                    projected[i][0] += 1.0F;
                    projected[i][1] += 1.0F;

                    projected[i][0] *= 0.5F * static_cast<float>(wnd.get_width());  // NOLINT
                    projected[i][1] *= 0.5F * static_cast<float>(wnd.get_height()); // NOLINT
                }

                rnd.draw_triangle(
                    r3d::vec2i{ { static_cast<int>(projected[0][0]), static_cast<int>(projected[0][1]) } },
                    r3d::vec2i{ { static_cast<int>(projected[1][0]), static_cast<int>(projected[1][1]) } },
                    r3d::vec2i{ { static_cast<int>(projected[2][0]), static_cast<int>(projected[2][1]) } },
                    white);
            }
        }

        rnd.update();
    }
}
