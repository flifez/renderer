//
// Created by flif3 on 8/1/2023.
//

#include "Ray.h"

namespace Raytracer {
    Vec3 Ray::at(double t) const {
        // takes parameter t (relative to `origin`) and returns the actual `Vec3`
        return origin + direction * t;
    }

    void Ray::setDirection(const Vec3 &dir) {
        direction = dir;
        direction = direction.normalize();
    }

    void Ray::setOrigin(const Vec3 &ori) {
        origin = ori;
    }
}