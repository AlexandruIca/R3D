#ifndef R3D_ASSERT_HPP
#define R3D_ASSERT_HPP
#pragma once

#include <cstdlib>
#include <string>

namespace r3d::impl {

auto fail(std::string const& file, int line, std::string const& msg) -> void;

}

#ifdef R3D_DEBUG

#define ASSERT(...)                                                                                                    \
    do {                                                                                                               \
        if(!(__VA_ARGS__)) {                                                                                           \
            r3d::impl::fail(__FILE__, __LINE__, #__VA_ARGS__);                                                         \
            exit(1);                                                                                                   \
        }                                                                                                              \
    } while(false)

#elif defined(R3D_RELEASE)

#define ASSERT(...) static_cast<void>(0);

#endif

#endif // !R3D_ASSERT_HPP
