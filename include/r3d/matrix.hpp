#ifndef R3D_MATRIX_HPP
#define R3D_MATRIX_HPP
#pragma once

#include <array>
#include <cstddef>
#include <type_traits>

#include "r3d/impl/assert.hpp"

namespace r3d {

namespace impl {

template<typename T, std::size_t N>
struct matrix
{
    static_assert(std::is_arithmetic_v<T>, "`r3d::matrix` type needs to be arithmetic");
    static_assert(N >= 1, "`r3d::matrix` size needs to be at least 1");

private:
    std::array<std::array<T, N>, N> m_data;

public:
    matrix(matrix const&) noexcept = default;
    matrix(matrix&&) noexcept = default;
    ~matrix() noexcept = default;

    explicit matrix(T const val)
    {
        for(auto& row : m_data) {
            row.fill(val);
        }
    }
    matrix()
        : matrix{ 0 }
    {
    }

    auto operator=(matrix const&) noexcept -> matrix& = default;
    auto operator=(matrix&&) noexcept -> matrix& = default;

    [[nodiscard]] auto operator()(int i, int j) noexcept -> T&
    {
        ASSERT(i >= 0);
        ASSERT(j >= 0);
        ASSERT(i < static_cast<int>(N));
        ASSERT(j < static_cast<int>(N));
        return m_data[static_cast<std::size_t>(i)][static_cast<std::size_t>(j)];
    }
    [[nodiscard]] auto operator()(int i, int j) const noexcept -> T const&
    {
        ASSERT(i >= 0);
        ASSERT(j >= 0);
        ASSERT(i < static_cast<int>(N));
        ASSERT(j < static_cast<int>(N));
        return m_data[static_cast<std::size_t>(i)][static_cast<std::size_t>(j)];
    }
};

} // namespace impl

using mat4f = impl::matrix<float, 4>;

} // namespace r3d

#endif // !R3D_MATRIX_HPP
