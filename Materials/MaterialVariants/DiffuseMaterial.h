//
// Created by flif3 on 8/1/2023.
//

#pragma once

#include "../Material.h"

namespace Raytracer {

    class DiffuseMaterial : public Material {
    public:
        DiffuseMaterial(const Vec3& color, float ambient, float diffuse) : color(color), ambient(ambient), diffuse(diffuse) {}

        Vec3 shade(const Vec3& lightDirection, const Vec3& normal, const Vec3& lightColor, const Vec3& lightIntensity) const override;
        Vec3 getColor() const override;

    private:
        Vec3 color;
        float ambient;
        float diffuse;
    };

} // Raytracer
