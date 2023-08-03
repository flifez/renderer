//
// Created by flif3 on 8/3/2023.
//

#pragma once

#include "../Material.h"

namespace Raytracer {

    class MirrorMaterial : public Material {
    public:
        MirrorMaterial(const Vec3& color, float reflectivity) : color(color), reflectivity(reflectivity) {}

        Vec3 shade(const Vec3& lightDirection, const Vec3& viewDirection, const Vec3& normal, const Vec3& lightColor, const Vec3& lightIntensity) const override;

        bool isReflective() override { return reflection; }
        bool isRefractive() const override { return refraction; }
        float getReflectivity() const override { return reflectivity; }
        float getRefractiveIndex() const override { return 0; }

    private:
        Vec3 color;
        float reflectivity;
        bool reflection = true;
        bool refraction = false;
    };

} // Raytracer
