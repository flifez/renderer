//
// Created by flif3 on 3/10/2024.
//

#include "AABB.h"

namespace Raytracer {
    bool AABB::contains(const Vec3& point) const {
        return (point.x >= min.x && point.x <= max.x) &&
               (point.y >= min.y && point.y <= max.y) &&
               (point.z >= min.z && point.z <= max.z);
    }

    bool AABB::intersects(const Raytracer::Ray& ray) const {
        float tmin = (min.x - ray.getOrigin().x) / ray.getDirection().x;
        float tmax = (max.x - ray.getOrigin().x) / ray.getDirection().x;

        if (tmin > tmax) std::swap(tmin, tmax);

        float tymin = (min.y - ray.getOrigin().y) / ray.getDirection().y;
        float tymax = (max.y - ray.getOrigin().y) / ray.getDirection().y;

        if (tymin > tymax) std::swap(tymin, tymax);

        if ((tmin > tymax) || (tymin > tmax))
            return false;

        if (tymin > tmin)
            tmin = tymin;

        if (tymax < tmax)
            tmax = tymax;

        float tzmin = (min.z - ray.getOrigin().z) / ray.getDirection().z;
        float tzmax = (max.z - ray.getOrigin().z) / ray.getDirection().z;

        if (tzmin > tzmax) std::swap(tzmin, tzmax);

        if ((tmin > tzmax) || (tzmin > tmax))
            return false;

        return true;
    }
} // Raytracer