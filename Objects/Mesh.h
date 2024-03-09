//
// Created by flif3 on 8/6/2023.
//

#pragma once

#include <vector>
#include "Object.h"
#include "../CodeHelper/Triangle.h"

namespace Raytracer {

    class Mesh : public Object  {
    public:
        Mesh() = default;
        Mesh(std::vector<Triangle> triangles, Material* material) : triangles(std::move(triangles)), Object(static_cast<std::shared_ptr<Material>>(material)) {}
        void addTriangle(const Triangle& triangle);
        const Triangle& getTriangle(int index) const;
        std::vector<Vec3> getVertices() const;
        int numberOfTriangles() const;
        void scale(float factor);

        void rotate(Vec3 euler);

        HitInfo intersectTriangle(const Ray& ray, const Triangle& triangle, int depth) const;
        HitInfo intersect(const Ray& ray, int depth) const override;
        AABB getBoundingBox() const override;

    private:
        std::vector<Triangle> triangles;
    };

} // Raytracer