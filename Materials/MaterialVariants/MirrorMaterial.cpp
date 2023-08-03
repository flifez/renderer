//
// Created by flif3 on 8/3/2023.
//

#include "MirrorMaterial.h"

namespace Raytracer {
Vec3 MirrorMaterial::shade(const Vec3& lightDirection, const Vec3& viewDirection, const Vec3& normal, const Vec3& lightColor, const Vec3& lightIntensity) const {
        Vec3 reflectionDirection = lightDirection.reflect(normal);
        return lightColor * lightIntensity * pow(std::max(0.0f, float(Vec3::dot(reflectionDirection, viewDirection))), 100);
    }
} // Raytracer