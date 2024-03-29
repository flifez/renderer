//
// Created by flif3 on 3/10/2024.
//

#include "BVH.h"

namespace Raytracer {
    AABB BVH::surrounding_box(const AABB& box0, const AABB& box1)
    {
        Vec3 small(fmin(box0.min.x, box1.min.x),
                   fmin(box0.min.y, box1.min.y),
                   fmin(box0.min.z, box1.min.z));

        Vec3 big(fmax(box0.max.x, box1.max.x),
                 fmax(box0.max.y, box1.max.y),
                 fmax(box0.max.z, box1.max.z));

        return {small, big};
    }
} // Raytracer