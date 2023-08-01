//
// Created by flif3 on 8/1/2023.
//

#pragma once

#include <memory>
#include <utility>
#include "../Materials/Material.h"
#include "../Ray/Ray.h"

namespace Raytracer {

    class HitInfo {
    public:
        float t;
        Vec3 point;
        Vec3 normal;
        std::shared_ptr<Material> material;

        HitInfo(float t, const Vec3& point, const Vec3& normal, std::shared_ptr<Material> material) : t(t), point(point), normal(normal), material(std::move(material)) {}
    };

    class Object {
    public:
        explicit Object(std::shared_ptr<Material> material) : material(std::move(material)) {}
        virtual ~Object() = default;

        std::shared_ptr<Material> getMaterial() const;

        virtual HitInfo intersect(const Ray& ray) const = 0; // to be implemented

    private:
        std::shared_ptr<Material> material;
    };

} // Raytracer
