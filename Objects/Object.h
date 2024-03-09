//
// Created by flif3 on 8/1/2023.
//

#pragma once

#include <memory>
#include <utility>
#include "../Materials/Material.h"
#include "../Ray/Ray.h"
#include "../Structures/AABB.h"

namespace Raytracer {

    class HitInfo {
    public:
        float t;
        Vec3 point;
        Vec3 normal;
        std::shared_ptr<Material> material;

        int depth = 0;

        HitInfo() : t(INFINITY), point(Vec3()), normal(Vec3()), material(nullptr), depth(MAX_DEPTH) {}

        HitInfo(float t, const Vec3& point, const Vec3& normal, std::shared_ptr<Material> material, int depth) :
        t(t),
        point(point),
        normal(normal),
        material(std::move(material)),
        depth(depth) {}
    };

    class Object {
    public:
        // Object() = default;
        explicit Object(std::shared_ptr<Material> material) : material(std::move(material)) {}
        virtual ~Object() = default;

        std::shared_ptr<Material> getMaterial() const;
        virtual AABB getBoundingBox() const = 0;
        virtual HitInfo intersect(const Ray& ray, int depth) const = 0;

    private:
        std::shared_ptr<Material> material;
    };

} // Raytracer

