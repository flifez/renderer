//
// Created by flif3 on 8/1/2023.
//

#pragma once

#include "../CodeHelper/Vec3.h"

namespace Raytracer {

    class Ray {
    public:
        Ray() = default;
        Ray(const Vec3 &origin, Vec3 direction) : origin(origin), direction(direction) {
            direction.normalize();
        }

        Vec3 at(double t) const;
        void setDirection(const Vec3 &dir);
        void setOrigin(const Vec3 &origin);

        Vec3 getDirection() const { return direction; }
        Vec3 getOrigin() const { return origin; }

        Ray reflect(const Vec3& point, const Vec3& normal) const;
        Ray refract(const Vec3& point, const Vec3& normal, double indexOfRefraction) const;

    private:
        Vec3 origin, direction;
    };
}