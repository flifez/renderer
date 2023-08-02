//
// Created by flif3 on 8/1/2023.
//

#pragma once

#include "../Light.h"

namespace Raytracer {

    class PointLight : public Light {
    public:
        PointLight(const Vec3& position, const Vec3& color, float intensity) : position(position), color(color), intensity(intensity) {}

        Vec3 getDirection(const Vec3& point) const override;
        Vec3 getIntensity(const Vec3& point) const override;
        Vec3 getColor() const override;

    private:
        Vec3 position;
        Vec3 color;
        float intensity;
    };

} // Raytracer
