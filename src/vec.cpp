#include "r3d/vec.hpp"

namespace r3d::operators {

auto operator*(vec3f const& v, mat4f const& m) -> vec3f
{
    vec3f result{ 0 };

    result[0] = v[0] * m(0, 0) + v[1] * m(1, 0) + v[2] * m(2, 0) + m(3, 0);
    result[1] = v[0] * m(0, 1) + v[1] * m(1, 1) + v[2] * m(2, 1) + m(3, 1);
    result[2] = v[0] * m(0, 2) + v[1] * m(1, 2) + v[2] * m(2, 2) + m(3, 2);
    float const w = v[0] * m(0, 3) + v[1] * m(1, 3) + v[2] * m(2, 3) + m(3, 3);

    if(w != 0) {
        result[0] /= w;
        result[1] /= w;
        result[2] /= w;
    }

    return result;
}

} // namespace r3d::operators
