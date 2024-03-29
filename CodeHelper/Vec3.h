//
// Created by flif3x on 7/31/2023.
//

#pragma once

#include <iostream>
#include "mathutil.h"
#include "constants.h"
#include <random>

namespace Raytracer {
    struct Vec3 {
        Vec3() : x(0), y(0), z(0) {} // default constructor
        explicit Vec3(double a) : x(a), y(a), z(a) {}
        Vec3(double x, double y, double z) : x(x), y(y), z(z) {} // parameterized
        static double dot(const Vec3 &a, const Vec3 &b); // dot product of two vec3
        static Vec3 cross(const Vec3 &a, const Vec3 &b); // cross product of two vec3
        static double euclideanDistance(const Vec3 &a, const Vec3 &b); // distance between two points
        static double angleBetween(Vec3 a, Vec3 b); // in radians; NAN for zero vectors
        static bool isPerpendicular(const Vec3 &a, const Vec3 &b);

        static bool areVec3Equal(const Vec3 &a, const Vec3 &b, double epsilon = 1e-06);

        Vec3 operator-() const; // negate

        static bool isParallel(Vec3 &a, Vec3 &b);
        double magnitude() const;
        Vec3 absComponents(); // make all components positive
        Vec3 negate() const;
        Vec3 normalize(); // convert to unit vector

        Vec3 reflect(const Vec3 &normal) const; // reflect vector about normal

        double x{}, y{}, z{};

        Vec3 operator+(const Vec3 &a) const;

        Vec3 operator-(const Vec3 &a) const;

        Vec3 operator*(const Vec3 &a) const;

        Vec3 operator*(double d) const;

        Vec3 operator/(double d) const;

        std::ostream &operator<<(std::ostream &os) const;

        Vec3 refract(const Vec3& v, double indexOfRefraction) const;

        static Vec3 random(double min, double max) ;
    };
}