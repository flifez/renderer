//
// Created by flif3 on 8/2/2023.
//

#pragma once

#include "../Light.h"

namespace Raytracer {

    class AreaLight {
        AreaLight(const Vec3& topLeftCorner, const Vec3& bottomRightCorner, const Vec3& color, float intensity) :
        topLeftCorner(topLeftCorner),
        bottomRightCorner(bottomRightCorner),
        color(color),
        intensity(intensity) {}

        // implement

    private:
        // "top left" and "bottom right": relative to the light side
        Vec3 topLeftCorner;
        Vec3 bottomRightCorner;
        Vec3 color;
        float intensity;
    };

} // Raytracer
