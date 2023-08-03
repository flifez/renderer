//
// Created by flif3 on 8/3/2023.
//

#include "MirrorMaterial.h"

namespace Raytracer {
Vec3 MirrorMaterial::shade(const Vec3& lightDirection, const Vec3& viewDirection, const Vec3& normal, const Vec3& lightColor, const Vec3& lightIntensity) const {
        // use reflectivity to determine how much of the light is reflected, and color to determine the color of the reflected light
        Vec3 reflectionDirection = lightDirection.reflect(normal);

        return lightColor * lightIntensity * std::max(0.0f, float(Vec3::dot(reflectionDirection, viewDirection))) * reflectivity * color;
    }
} // Raytracer