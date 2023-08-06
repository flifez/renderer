//
// Created by flif3 on 8/6/2023.
//

#include "Mesh.h"

namespace Raytracer {
    void Mesh::addTriangle(const Triangle& triangle) {
        triangles.push_back(triangle);
    }

    const Triangle& Mesh::getTriangle(int index) const {
        return triangles[index];
    }

    int Mesh::numberOfTriangles() const {
        return triangles.size();
    }

    HitInfo Mesh::intersectTriangle(const Raytracer::Ray& ray, const Raytracer::Triangle& triangle, int depth) const {
        /* Ray-triangle intersection using the Moeller-Trumbore algorithm
         * Moeller-Trumbore Algorithm explained: https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
         * */

        Vec3 e1 = triangle.getV1() - triangle.getV0();
        Vec3 e2 = triangle.getV2() - triangle.getV0();
        Vec3 h = Vec3::cross(ray.getDirection(), e2);

        // Check if ray is parallel to triangle
        auto a = float(Vec3::dot(e1, h));
        if (a > -std::numeric_limits<float>::epsilon() && a < std::numeric_limits<float>::epsilon()) {
            return {};
        }

        // Check if ray is pointing away from triangle
        float f = 1.0f / a;
        Vec3 s = ray.getOrigin() - triangle.getV0();
        float u = f * float(Vec3::dot(s, h));

        if (u < 0.0f || u > 1.0f) {
            return {};
        }

        Vec3 q = Vec3::cross(s, e1);
        auto v = f * float(Vec3::dot(ray.getDirection(), q));

        if (v < 0.0f || u + v > 1.0f) {
            return {};
        }

        float t = f * float(Vec3::dot(e2, q));

        if (t > std::numeric_limits<float>::epsilon()) {
            Vec3 point = ray.at(t);
            Vec3 normal = Vec3::cross(e1, e2).normalize();
            return {t, point, normal, getMaterial(), depth};
        }

        return {};
    }

    HitInfo Mesh::intersect(const Raytracer::Ray& ray, int depth) const {
        HitInfo closestHit;

        for (const auto& triangle : triangles) {
            HitInfo hit = intersectTriangle(ray, triangle, depth);
            if (hit.t < closestHit.t) {
                closestHit = hit;
            }
        }

        return closestHit;
    }
} // Raytracer