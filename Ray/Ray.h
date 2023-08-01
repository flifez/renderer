//
// Created by flif3 on 8/1/2023.
//

#pragma once

#include "../CodeHelper/Vec3.h"

namespace Raytracer {

    struct Ray {
        Vec3 origin, direction;

        Ray(const Vec3 &origin, Vec3 direction) : origin(origin), direction(direction) {
            direction = direction.normalize();
        }

        Vec3 at(double t) const;
        void setDirection(const Vec3 &dir);
        void setOrigin(const Vec3 &origin);
    };
}