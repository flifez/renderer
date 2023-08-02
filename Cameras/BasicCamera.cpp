//
// Created by flif3 on 8/1/2023.
//

#include "BasicCamera.h"

namespace Raytracer {

    Ray BasicCamera::generateRay(float x, float y) const {
        float scale = std::tan(fov * 0.5);
        float imageX = (2 * x - 1) * scale;
        float imageY = (1 - 2 * y) * scale * aspectRatio;
        Vec3 direction = Vec3(imageX, imageY, -1).normalize();
        return {position, direction};
    }

    Vec3 BasicCamera::getDirection(const Vec3& point) const {
        return (point - position).normalize();
    }

}