//
// Created by flif3 on 8/6/2023.
//

#pragma once

#include <vector>
#include "Vec3.h"

namespace Raytracer {

    class Triangle {
    public:
        Triangle(const Vec3& v1, const Vec3& v2, const Vec3& v3) : v0(v1), v1(v2), v2(v3) {}
        Vec3 getV0() const { return v0; }
        Vec3 getV1() const { return v1; }
        Vec3 getV2() const { return v2; }

    private:
        Vec3 v0, v1, v2;
    };

} // Raytracer
