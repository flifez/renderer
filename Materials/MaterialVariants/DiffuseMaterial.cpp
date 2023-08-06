//
// Created by flif3 on 8/1/2023.
//

#include "DiffuseMaterial.h"

namespace Raytracer {
    Vec3 DiffuseMaterial::shade(const Vec3 &lightDirection, const Vec3& viewDirection, const Vec3 &normal, const Vec3 &lightColor, const Vec3& lightIntensity, const Vec3& ambient) const {
        double diffuseIntensity = std::max(0.0f, float(Vec3::dot(normal, lightDirection)));
        Vec3 diffuseColor = lightColor * color * lightIntensity * diffuse * diffuseIntensity;
        return ambient * color + diffuseColor;
    }
} // Raytracer