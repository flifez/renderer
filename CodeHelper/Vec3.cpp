//
// Created by flif3 on 8/2/2023.
//

#include "Vec3.h"

namespace Raytracer {
    double Vec3::dot(const Vec3 &a, const Vec3 &b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    Vec3 Vec3::cross(const Vec3 &a, const Vec3 &b) {
        return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
    }

    double Vec3::euclideanDistance(const Vec3 &a, const Vec3 &b) {
        double dx = a.x - b.x;
        double dy = a.y - b.y;
        double dz = a.z - b.z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }

    double Vec3::angleBetween(Vec3 a, Vec3 b) {
        double dotP = dot(a, b);
        double aLength = a.magnitude();
        double bLength = b.magnitude();
        if (dotP != 0 && aLength != 0 && bLength != 0) {
            double cosineValue = dotP / (aLength * bLength);
            return std::acos(cosineValue);
        }
        return NAN;
    }

    bool Vec3::isPerpendicular(const Vec3 &a, const Vec3 &b) {
        return (dot(a, b) == 0);
    }

    Vec3 Vec3::operator-() const {
        return this->negate();
    }

    bool Vec3::isParallel(Vec3 &a, Vec3 &b) {
        return areVec3Equal(a, b);
    }

    double Vec3::magnitude() const {
        static const Vec3 origin = Vec3(0, 0, 0);
        return euclideanDistance(*this, origin);
    }

    Vec3 Vec3::absComponents() {
        x = std::abs(x);
        y = std::abs(y);
        z = std::abs(z);
        return {x, y, z};
    }

    Vec3 Vec3::negate() const {
        return {-x, -y, -z};
    }

    Vec3 Vec3::normalize() {
        double length = magnitude();
        if (length != 0) {
            x /= length;
            y /= length;
            z /= length;
            return {x, y, z};
        }
        return {0, 0, 0};
    }

    Vec3 Vec3::operator+(const Vec3 &a) const {
        return {x + a.x, y + a.y, z + a.z};
    }

    Vec3 Vec3::operator-(const Vec3 &a) const {
        return {x - a.x, y - a.y, z - a.z};
    }

    Vec3 Vec3::operator*(const Vec3 &a) const {
        return {x * a.x, y * a.y, z * a.z};
    }

    Vec3 Vec3::operator*(double d) const {
        return {this->x * d, this->y * d, this->z * d};
    }

    Vec3 Vec3::operator/(double d) const {
        return {this->x / d, this->y / d, this->z / d};
    }

    Vec3 operator*(double d, const Vec3 &v) {
        return {v.x * d, v.y * d, v.z * d};
    }

    bool operator==(const Vec3 &a, const Vec3 &b) {
        return (a.x == b.x && a.y == b.y && a.z == b.z);
    }

    bool operator!=(const Vec3 &a, const Vec3 &b) {
        return !(a == b);
    }

    std::ostream &operator<<(std::ostream &os, const Vec3 &a) {
        return os << "[" << a.x << ", " << a.y << ", " << a.z << "]";
    }

    bool Vec3::areVec3Equal(const Vec3 &a, const Vec3 &b, double epsilon) {
        Vec3 diff = a - b;
        return (epsilonComparison(diff.x, epsilon) && epsilonComparison(diff.y, epsilon) &&
                epsilonComparison(diff.z, epsilon));
    }
}