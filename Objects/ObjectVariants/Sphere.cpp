//
// Created by flif3 on 8/1/2023.
//

#include "Sphere.h"

namespace Raytracer {
    HitInfo Sphere::intersect(const Ray& ray, int depth) const {
        Vec3 oc = ray.getOrigin() - position;
        float a = Vec3::dot(ray.getDirection(), ray.getDirection());
        float b = 2.0f * Vec3::dot(oc, ray.getDirection());
        float c = Vec3::dot(oc, oc) - radius * radius;
        float discriminant = b * b - 4 * a * c;

        if (discriminant < 0) {
            return {};
        } else {
            float t = (-b - std::sqrt(discriminant)) / (2.0f * a);
            Vec3 point = ray.at(t);
            Vec3 normal = (point - position).normalize();
            return {t, point, normal, Raytracer::Sphere::getMaterial(), depth};
        }
    }
}