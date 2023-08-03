//
// Created by flif3 on 8/2/2023.
//

#pragma once

#include "../Material.h"

namespace Raytracer {
    class BlinnPhongMaterial : public Material {
    public:
        BlinnPhongMaterial(const Vec3& color, float diffuse, float specular, float shininess)
                : color(color), diffuse(diffuse), specular(specular), shininess(shininess) {}

        Vec3 shade(const Vec3& lightDirection, const Vec3& viewDirection, const Vec3& normal, const Vec3& lightColor, const Vec3& lightIntensity) const override;


    private:
        Vec3 color;
        float diffuse;
        float specular;
        float shininess;
        bool reflective = true;
        bool refractive = false;
    };
} // Raytracer
