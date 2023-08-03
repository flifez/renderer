//
// Created by flif3 on 8/1/2023.
//

#pragma once

#include "../Material.h"

namespace Raytracer {

    class DiffuseMaterial : public Material {
    public:
        DiffuseMaterial(const Vec3& color, float diffuse) : color(color), diffuse(diffuse) {}

        Vec3 shade(const Vec3& lightDirection, const Vec3& viewDirection, const Vec3& normal, const Vec3& lightColor, const Vec3& lightIntensity) const override;

        bool isReflective() override { return reflective; }
        bool isRefractive() const override { return refractive; }

    private:
        Vec3 color;
        float diffuse;
        bool reflective = false;
        bool refractive = false;
    };

} // Raytracer
