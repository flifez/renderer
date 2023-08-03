//
// Created by flif3 on 8/1/2023.
//

#pragma once

#include "../CodeHelper/Vec3.h"

namespace Raytracer {

    class Material {
    public:
        virtual ~Material() = default;
        virtual Vec3 shade(const Vec3& lightDirection, const Vec3& viewDirection, const Vec3& normal, const Vec3& lightColor, const Vec3& lightIntensity) const = 0;
        virtual Vec3 getColor() { return color; };
        virtual bool isReflective() { return reflective; }
        virtual bool isRefractive() const { return refractive; }
        virtual float getReflectivity() const { return 0; }
        virtual float getRefractiveIndex() const { return 0; }
        virtual float getTransparency() const { return 0; }

    protected:
        bool reflective;
        bool refractive;
        Vec3 color;
    };

} // Raytracer
