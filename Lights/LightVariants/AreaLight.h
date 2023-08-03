//
// Created by flif3 on 8/2/2023.
//

#pragma once

#include "../Light.h"

namespace Raytracer {

    class AreaLight : public Light {
    public:
        AreaLight(const Vec3& position, const Vec3& normal, const Vec3& color, float intensity, float width, float height) :
        position(position),
        normal(normal),
        color(color),
        intensity(intensity),
        width(width),
        height(height) {}

        Vec3 getDirection(const Vec3& point) const override;
        Vec3 getIntensity(const Vec3& point) const override;
        Vec3 getColor() const override;

    private:
        Vec3 position;
        Vec3 normal;
        Vec3 color;
        float intensity;
        float width, height;
    };

} // Raytracer
