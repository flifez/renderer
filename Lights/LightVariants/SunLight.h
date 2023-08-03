//
// Created by flif3 on 8/2/2023.
//

#pragma once

#include "../Light.h"

namespace Raytracer {

    class SunLight : public Light {
    public:
        SunLight(const Vec3& direction, const Vec3& color, float intensity)
        : direction(direction), color(color), intensity(intensity) {}

        Vec3 getDirection(const Vec3& point) const override;
        Vec3 getIntensity(const Vec3& point) const override;
        Vec3 getColor() const override;

    private:
        Vec3 direction;
        Vec3 color;
        float intensity;
    };

} // Raytracer
