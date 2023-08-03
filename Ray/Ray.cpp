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

    Ray Ray::reflect(const Vec3& point, const Vec3& normal) const {
        Vec3 reflectedDirection = direction.reflect(normal);
        Ray reflectedRay;
        reflectedRay.setDirection(reflectedDirection);
        reflectedRay.setOrigin(point);
        return reflectedRay;
    }

    Ray Ray::refract(const Vec3& point, const Vec3& normal, double indexOfRefraction) const {
        Vec3 refractedDirection = direction.refract(normal, indexOfRefraction);
        Ray refractedRay;
        refractedRay.setDirection(refractedDirection);
        refractedRay.setOrigin(point);
        return refractedRay;
    }
}