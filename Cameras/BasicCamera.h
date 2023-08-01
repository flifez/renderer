//
// Created by flif3 on 8/1/2023.
//

#pragma once

#include "../Ray/Ray.h"

namespace Raytracer {
    class BasicCamera {
    public:
        BasicCamera(const Vec3 &position, const Vec3 &orientation, float fov, float aspectRatio) : position(position), orientation(orientation),
                                                                          fov(fov), aspectRatio(aspectRatio) {}

        Ray generateRay(float x, float y) const;

    private:
        Vec3 position, orientation;
        float fov;
        float aspectRatio;
    };
}