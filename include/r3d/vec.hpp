#ifndef R3D_VEC_HPP
#define R3D_VEC_HPP
#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <functional>
#include <iostream>
#include <numeric>
#include <type_traits>

#include "r3d/impl/assert.hpp"
#include "r3d/matrix.hpp"

namespace r3d {

namespace impl {

template<typename T, std::size_t N>
struct vec
{
    static_assert(std::is_arithmetic_v<T>, "`r3d::vec` can only accept arithmetic types");
    static_assert(N >= 1, "`r3d::vec` needs to have size at least 1");

private:
    std::array<T, N> m_data;

public:
    vec(vec const&) noexcept = default;
    vec(vec&&) noexcept = default;
    ~vec() noexcept = default;

    explicit vec(std::array<T, N> const& init)
        : m_data{ init }
    {
    }

    explicit vec(T const& val)
    {
        m_data.fill(val);
    }

    vec()
        : vec(0)
    {
    }

    auto operator=(vec const&) noexcept -> vec& = default;
    auto operator=(vec&&) noexcept -> vec& = default;

    [[nodiscard]] constexpr auto size() const noexcept -> std::size_t
    {
        return N;
    }

    [[nodiscard]] auto operator==(vec const& other) const noexcept -> bool
    {
        return m_data == other.m_data;
    }
    [[nodiscard]] auto operator!=(vec const& other) const noexcept -> bool
    {
        return !(m_data == other.m_data);
    }

    [[nodiscard]] auto operator+(vec const& other) const noexcept -> vec
    {
        vec tmp{ 0 };
        std::transform(m_data.begin(), m_data.end(), other.m_data.begin(), tmp.m_data.begin(), std::plus<>{});
        return tmp;
    }
    [[nodiscard]] auto operator-(vec const& other) const noexcept -> vec
    {
        vec tmp{ 0 };
        std::transform(m_data.begin(), m_data.end(), other.m_data.begin(), tmp.m_data.begin(), std::minus<>{});
        return tmp;
    }

    [[nodiscard]] auto operator+(T const val) const noexcept -> vec
    {
        vec result{ *this };

        for(T& t : result.m_data) {
            t += val;
        }

        return result;
    }
    [[nodiscard]] auto operator-(T const val) const noexcept -> vec
    {
        vec result{ *this };

        for(T& t : result.m_data) {
            t -= val;
        }

        return result;
    }
    [[nodiscard]] auto operator*(T const val) const noexcept -> vec
    {
        vec result{ *this };

        for(T& t : result.m_data) {
            t *= val;
        }

        return result;
    }
    [[nodiscard]] auto operator/(T const val) const noexcept -> vec
    {
        vec result{ *this };

        for(T& t : result.m_data) {
            t /= val;
        }

        return result;
    }

    [[nodiscard]] auto operator[](int const index) noexcept -> T&
    {
        ASSERT(index >= 0);
        ASSERT(static_cast<std::size_t>(index) < N);
        return m_data[static_cast<std::size_t>(index)];
    }
    [[nodiscard]] auto operator[](int const index) const noexcept -> T const&
    {
        ASSERT(index >= 0);
        ASSERT(static_cast<std::size_t>(index) < N);
        return m_data[static_cast<std::size_t>(index)];
    }
    [[nodiscard]] auto operator[](std::size_t const index) noexcept -> T&
    {
        ASSERT(index < N);
        return m_data[index];
    }
    [[nodiscard]] auto operator[](std::size_t const index) const noexcept -> T const&
    {
        ASSERT(index < N);
        return m_data[index];
    }

    [[nodiscard]] auto length() const noexcept -> float
    {
        return std::sqrt(std::accumulate(
            m_data.begin(), m_data.end(), T{ 0 }, [](T const sum, T const val) -> T { return sum + val * val; }));
    }

    auto normalize() noexcept -> void
    {
        float const len = this->length();

        for(T& num : m_data) {
            num /= len;
        }
    }
};

} // namespace impl

using vec2i = impl::vec<int, 2>;
using vec3f = impl::vec<float, 3>;
using vec4f = impl::vec<float, 4>;
using triangle = std::array<vec3f, 3>;

template<typename T, std::size_t N>
[[nodiscard]] auto cross(impl::vec<T, N> const& v1, impl::vec<T, N> const& v2) -> impl::vec<T, N>
{
    impl::vec<T, N> result{ 0 };

    constexpr int x = 0;
    constexpr int y = 1;
    constexpr int z = 2;

    result[x] = v1[y] * v2[z] - v1[z] * v2[y];
    result[y] = v1[z] * v2[x] - v1[x] * v2[z];
    result[z] = v1[x] * v2[y] - v1[y] * v2[x];

    return result;
}

template<typename T, std::size_t N>
[[nodiscard]] auto dot(impl::vec<T, N> const& v1, impl::vec<T, N> const& v2) -> T
{
    T result{ 0 };

    for(std::size_t i = 0; i < N; ++i) {
        result += v1[i] * v2[i];
    }

    return result;
}

namespace operators {

[[nodiscard]] auto operator*(vec3f const& v, mat4f const& m) -> vec3f;

template<typename T, std::size_t N>
auto operator<<(std::ostream& os, impl::vec<T, N> const& v) -> std::ostream&
{
    os << '(';
    os << v[0];

    for(std::size_t i = 1; i < N; ++i) {
        os << ", " << v[i];
    }

    os << ')';
    return os;
}

} // namespace operators

} // namespace r3d

#endif // !R3D_VEC_HPP
