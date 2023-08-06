//
// Created by flif3 on 8/6/2023.
//

#pragma once

#include "Triangle.h"

namespace Raytracer {

    class TriangleList {
    public:
        void addTriangle(const Vec3& vec3_0, const Vec3& vec3_1, const Vec3& vec3_2);
        void addTriangle(const Triangle& triangle);
        const Triangle& getTriangle(int index) const;
        int numberOfTriangles() const;

    private:
        std::vector<Triangle> triangles;

    };

} // Raytracer