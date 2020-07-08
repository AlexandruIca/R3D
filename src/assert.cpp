#include "r3d/impl/assert.hpp"
#include "r3d/impl/log.hpp"

namespace r3d::impl {

auto fail(std::string const& file, int const line, std::string const& msg) -> void
{
    spdlog::error("{}[{}] Assertion failed: {}", file, line, msg);
}

} // namespace r3d::impl
