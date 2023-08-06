//
// Created by flif3 on 8/6/2023.
//

#pragma once

#include <vector>
#include "Object.h"
#include "../CodeHelper/Triangle.h"

namespace Raytracer {

    class Mesh : public Object {
    public:
        void addTriangle(const Triangle& triangle);
        const Triangle& getTriangle(int index) const;
        int numberOfTriangles() const;

        HitInfo intersectTriangle(const Ray& ray, const Triangle& triangle, int depth) const;
        HitInfo intersect(const Ray& ray, int depth) const override;

    private:
        std::vector<Triangle> triangles;
    };

} // Raytracer