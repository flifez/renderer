//
// Created by flif3 on 8/2/2023.
//

#include "BlinnPhongMaterial.h"

namespace Raytracer {

    Vec3 BlinnPhongMaterial::shade(const Vec3& lightDirection, const Vec3& viewDirection, const Vec3& normal, const Vec3& lightColor, const Vec3& lightIntensity, const Vec3& ambient) const {
        Vec3 halfVector = (lightDirection + viewDirection).normalize();
        Vec3 reflectionDirection = -lightDirection.reflect(normal);

        double diffuseIntensity = std::max(0.0f, float(Vec3::dot(normal, lightDirection)));
        double specularIntensity = std::pow(std::max(0.0f, float(Vec3::dot(normal, halfVector))), shininess);

        Vec3 diffuseColor = lightColor * color * diffuse * diffuseIntensity * lightIntensity;
        Vec3 specularColor = lightColor * specular * specularIntensity * lightIntensity;

        return ambient * color + diffuseColor + specularColor;
    }
} // Raytracer