//
// Created by flif3 on 8/2/2023.
//

#define _USE_MATH_DEFINES // VS Code specific
#include <cmath>

#include "AreaLight.h"
#include <random>

namespace Raytracer {
    Vec3 AreaLight::getDirection(const Vec3& point) const {
        std::default_random_engine generator;
        std::uniform_real_distribution<double> distribution(-0.5, 0.5);

        // Rand point within the area light
        Vec3 randomPoint = position + Vec3::cross(normal, Vec3(0, 1, 0)) * distribution(generator) * width
                + Vec3::cross(normal, Vec3(1, 0, 0)) * distribution(generator) * height;

        return (randomPoint - point).normalize();
    }

    Vec3 AreaLight::getIntensity(const Raytracer::Vec3& point) const {
        double distance = (position - point).magnitude();
        double distanceSquared = distance * distance;
        return color * intensity / (4 * M_PI * distanceSquared);
    }

    Vec3 AreaLight::getColor() const {
        return color;
    }
} // Raytracer