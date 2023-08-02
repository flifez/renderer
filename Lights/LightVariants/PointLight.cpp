//
// Created by flif3 on 8/1/2023.
//

#include "PointLight.h"

namespace Raytracer {
    Vec3 PointLight::getDirection(const Vec3 &point) const {
        return (position - point).normalize();
    }

    Vec3 PointLight::getIntensity(const Vec3 &point) const {
        double distance = (position - point).magnitude();
        double distanceSquared = distance * distance;
        return color * intensity / (4 * M_PI * distanceSquared);
    }

    Vec3 PointLight::getColor() const {
        return color;
    }
} // Raytracer