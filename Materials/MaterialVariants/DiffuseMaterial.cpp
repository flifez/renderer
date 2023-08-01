//
// Created by flif3 on 8/1/2023.
//

#include "DiffuseMaterial.h"

namespace Raytracer {
    Vec3 DiffuseMaterial::shade(const Vec3 &lightDirection, const Vec3 &normal, const Vec3 &lightColor, const Vec3& lightIntensity) const {
        double diffuseIntensity = std::max(0.0f, float(Vec3::dot(normal, -lightDirection)));
        Vec3 diffuseColor = lightColor * color * lightIntensity * diffuse * diffuseIntensity;
        Vec3 ambientColor = lightColor * color * lightIntensity * ambient;
        return diffuseColor + ambientColor;
    }

    Vec3 DiffuseMaterial::getColor() const {
        return color;
    }
} // Raytracer