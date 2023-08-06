//
// Created by flif3 on 8/6/2023.
//

#include "Triangle.h"
#include "TriangleList.h"


namespace Raytracer {
    void TriangleList::addTriangle(const Vec3& vec3_0, const Vec3& vec3_1, const Vec3& vec3_2) {
        Triangle triangle(vec3_0, vec3_1, vec3_2);
        triangles.push_back(triangle);
    }

    void TriangleList::addTriangle(const Triangle& triangle) {
        triangles.push_back(triangle);
    }

    const Triangle& TriangleList::getTriangle(int index) const {
        if (index < 0 || index * 3 + 2 >= triangles.size()) {
            throw std::out_of_range("Index out of range");
        }
        return triangles[index * 3];
    }

    int TriangleList::numberOfTriangles() const {
        return triangles.size() / 3;
    }
} // Raytracer