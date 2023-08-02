//
// Created by flif3 on 8/1/2023.
//

#pragma once

#include "../Object.h"

namespace Raytracer {

    class Sphere : public Object {
    public:
        Sphere(Material *material, const Vec3 &position, float radius) : Object(
                static_cast<std::shared_ptr<Material>>(material)),
                                                                         position(position),
                                                                         radius(radius) {}

        HitInfo intersect(const Ray& ray) const override;
    private:
        Vec3 position;
        float radius;
    };
}