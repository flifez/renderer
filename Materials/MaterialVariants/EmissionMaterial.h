//
// Created by flif3 on 8/4/2023.
//

#pragma once

#include "../Material.h"

namespace Raytracer {

    class EmissionMaterial : public Material {
        // emits light from the surface. For each point on the surface, the direction of the light is the normal of the surface at that point.
    public:
        EmissionMaterial(const Vec3& color, float intensity) :
        color(color),
        intensity(intensity) {}

        // Vec3 getColor(const Vec3& point) const override;
        // Vec3 getDirection(const Vec3& point) const override;
        // Vec3 getIntensity(const Vec3& point) const override;

    private:
        Vec3 color;
        float intensity;


    };

} // Raytracer
