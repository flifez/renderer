//
// Created by flif3 on 8/1/2023.
//

#pragma once

#include "../CodeHelper/Vec3.h"

namespace Raytracer {

    class Light {
    public:
        virtual ~Light() = default;
        virtual Vec3 getDirection(const Vec3& point) const = 0;
        virtual Vec3 getIntensity(const Vec3& point) const = 0;
        virtual Vec3 getColor() const = 0;
    };

} // Raytracer
