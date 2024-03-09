//
// Created by flif3 on 8/1/2023.
//

#pragma once

#include <vector>
#include "../Cameras/BasicCamera.h"
#include "../Objects/Object.h"
#include "../Lights/Light.h"
#include "../Structures/BVH.h"

namespace Raytracer {

    class Scene {
    public:
        explicit Scene(const BasicCamera& camera) : camera(camera) {}

        void addObject(const std::shared_ptr<Object>& object);
        void addLight(const std::shared_ptr<Light>& light);
        void setAmbient(const Vec3& ambientColor, float ambientIntensity);


        const std::vector<std::shared_ptr<Object>>& getObjects() const;
        const std::vector<std::shared_ptr<Light>>& getLights() const;
        BasicCamera getCamera() const;
        const Vec3& getAmbient() const;

        HitInfo findClosestIntersection(const Ray& ray, int depth) const;
    private:
        BasicCamera camera;
        std::vector<std::shared_ptr<Object>> objects;
        BVH bvh;
        std::vector<std::shared_ptr<Light>> lights;
        Vec3 ambientColor;
        float ambientIntensity;
        Vec3 ambient;
    };

} // Raytracer
