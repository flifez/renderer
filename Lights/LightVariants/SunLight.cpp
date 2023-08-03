//
// Created by flif3 on 8/2/2023.
//

#include "SunLight.h"

namespace Raytracer {
    Vec3 SunLight::getDirection(const Vec3& point) const {
        return direction;
    }

    Vec3 SunLight::getIntensity(const Vec3& point) const {
        return color * intensity;
    }

    Vec3 SunLight::getColor() const {
        return color;
    }
} // Raytracer