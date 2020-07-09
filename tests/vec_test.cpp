#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <utility>

#include "r3d/vec.hpp"

TEST_CASE("[vec2i] Addition/Substraction/Scalar-Multiplication/Division and equality")
{
    constexpr int val1 = 5;
    constexpr int val2 = 10;

    using vec2i = r3d::impl::vec<int, 2>;
    using arr2i = std::array<int, 2>;

    vec2i v1{ val1 };
    vec2i v2{ val2 };

    REQUIRE(v1.size() == 2);
    REQUIRE(v2.size() == v1.size());
    REQUIRE(v1 != v2);
    REQUIRE(v1 + v2 == vec2i{ arr2i{ { 15, 15 } } });
    REQUIRE(v2 - v1 == vec2i{ arr2i{ { 5, 5 } } });
    REQUIRE(v1 + 5 == v2);
    REQUIRE(v2 - 5 == v1);
    REQUIRE(v1 * 2 == v2);
    REQUIRE(v2 / 2 == v1);
}

TEST_CASE("[vec2i] Copy")
{
    using vec2i = r3d::impl::vec<int, 2>;
    using arr2i = std::array<int, 2>;

    vec2i v1{ arr2i{ 1, 2 } };
    vec2i v2 = v1;

    REQUIRE(v2 == v1);
    REQUIRE(v2.size() == 2);

    vec2i v3{ 0 };
    v3 = v2;

    REQUIRE(v3 == v1);
}

TEST_CASE("[vec4i] Index")
{
    using vec4i = r3d::impl::vec<int, 4>;
    using arr4i = std::array<int, 4>;

    vec4i v{ arr4i{ 1, 2, 3, 4 } };

    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);
    REQUIRE(v[3] == 4);
}

TEST_CASE("[vec3fxmat4f]")
{
    r3d::vec3f v{ 1 };
    r3d::mat4f m{ 1 };

    using namespace r3d::operators;
    using arr3f = std::array<float, 3>;

    REQUIRE(v * m == r3d::vec3f{ arr3f{ 1, 1, 1 } });
}
