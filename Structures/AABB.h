//
// Created by flif3 on 3/10/2024.
//

#pragma once

#include "../CodeHelper/Vec3.h"
#include "../Ray/Ray.h"

namespace Raytracer {
    class Object;

    class AABB {
    public:
        Vec3 min; // minimum point
        Vec3 max; // maximum point

        AABB() : min(Vec3(0, 0, 0)), max(Vec3(0, 0, 0)) {}
        AABB(const Vec3& min, const Vec3& max) : min(min), max(max) {}

        bool contains(const Vec3& point) const;
        bool intersects(const Ray& ray) const;
    };
} // Raytracer
