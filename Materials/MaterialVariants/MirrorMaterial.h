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

    private:
        Vec3 color;
        float reflectivity;
    };

} // Raytracer
