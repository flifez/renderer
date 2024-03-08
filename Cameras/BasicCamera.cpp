//
// Created by flif3 on 8/1/2023.
//

#include "BasicCamera.h"

namespace Raytracer {

    Ray BasicCamera::generateRay(float x, float y) const {
        float scale = std::tan(fov * 0.5);
        float imageX = (2 * x - 1) * scale;
        float imageY = (1 - 2 * y) * scale * aspectRatio;

        double orientationX = orientation.x;
        double orientationY = orientation.y;
        double orientationZ = orientation.z;

        Vec3 direction = Vec3(imageX - orientationX, imageY - orientationY, -orientationZ).normalize();
        // std::cout << direction.x << direction.y << direction.z << std::endl;
        return {position, direction};
    }

    Vec3 BasicCamera::getDirection(const Vec3& point) const {
        return (point - position).normalize();
    }

}