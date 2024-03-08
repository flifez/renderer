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
        Vec3 h = Vec3::cross(ray.getDirection().normalize(), e2);

        // Check if ray is parallel to triangle
        auto a = float(Vec3::dot(e1, h));
        if (a > -std::numeric_limits<float>::epsilon() && a < std::numeric_limits<float>::epsilon()) {
            return {};
        }

        // Check if ray is pointing away from triangle
        float f = 1.0f / a;
        Vec3 s = -(triangle.getV0() - ray.getOrigin());
        float u = f * float(Vec3::dot(s, h));

        if (u < 0.0f || u > 1.0f) {
            return {};
        }

        Vec3 q = Vec3::cross(s, e1);
        auto v = f * float(Vec3::dot(ray.getDirection().normalize(), q));

        if (v < 0.0f || u + v > 1.0f) {
            return {};
        }

        float t = f * float(Vec3::dot(e2, q));

        // debug
        // std::cout << "t: " << t << std::endl;

        if (t > std::numeric_limits<float>::epsilon()) {
            Vec3 point = ray.at(t);
            Vec3 normal = -Vec3::cross(e1, e2).normalize();
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

    void Mesh::scale(float factor) {
        for (auto& triangle : triangles) {
            triangle.setV0(triangle.getV0() * factor);
            triangle.setV1(triangle.getV1() * factor);
            triangle.setV2(triangle.getV2() * factor);
        }
    }

    void Mesh::rotate(Vec3 euler) {
        float cosPitch = cos(euler.x);
        float sinPitch = sin(euler.x);
        float cosYaw = cos(euler.y);
        float sinYaw = sin(euler.y);
        float cosRoll = cos(euler.z);
        float sinRoll = sin(euler.z);

        // Rotation matrix elements
        float r00 = cosYaw * cosPitch;
        float r01 = cosYaw * sinPitch * sinRoll - sinYaw * cosRoll;
        float r02 = cosYaw * sinPitch * cosRoll + sinYaw * sinRoll;

        float r10 = sinYaw * cosPitch;
        float r11 = sinYaw * sinPitch * sinRoll + cosYaw * cosRoll;
        float r12 = sinYaw * sinPitch * cosRoll - cosYaw * sinRoll;

        float r20 = -sinPitch;
        float r21 = cosPitch * sinRoll;
        float r22 = cosPitch * cosRoll;

        for (auto& triangle : triangles) {
            triangle.setV0(Vec3(
                    r00 * triangle.getV0().x + r01 * triangle.getV0().y + r02 * triangle.getV0().z,
                    r10 * triangle.getV0().x + r11 * triangle.getV0().y + r12 * triangle.getV0().z,
                    r20 * triangle.getV0().x + r21 * triangle.getV0().y + r22 * triangle.getV0().z
            ));
            triangle.setV1(Vec3(
                    r00 * triangle.getV1().x + r01 * triangle.getV1().y + r02 * triangle.getV1().z,
                    r10 * triangle.getV1().x + r11 * triangle.getV1().y + r12 * triangle.getV1().z,
                    r20 * triangle.getV1().x + r21 * triangle.getV1().y + r22 * triangle.getV1().z
            ));
            triangle.setV2(Vec3(
                    r00 * triangle.getV2().x + r01 * triangle.getV2().y + r02 * triangle.getV2().z,
                    r10 * triangle.getV2().x + r11 * triangle.getV2().y + r12 * triangle.getV2().z,
                    r20 * triangle.getV2().x + r21 * triangle.getV2().y + r22 * triangle.getV2().z
            ));
        }
    }
} // Raytracer