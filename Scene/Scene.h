//
// Created by flif3 on 8/1/2023.
//

#pragma once

#include <vector>
#include "../Cameras/BasicCamera.h"
#include "../Objects/Object.h"
#include "../Lights/Light.h"

namespace Raytracer {

    class Scene {
    public:
        explicit Scene(const BasicCamera& camera) : camera(camera) {}

        void addObject(std::shared_ptr<Object> object);
        void addLight(std::shared_ptr<Light> light);
        void setAmbientLight(const Vec3& ambientLight);


        const std::vector<std::shared_ptr<Object>>& getObjects() const;
        const std::vector<std::shared_ptr<Light>>& getLights() const;
        BasicCamera getCamera() const;
        const Vec3& getAmbientLight() const;

        HitInfo findClosestIntersection(const Ray& ray) const;
    private:
        BasicCamera camera;
        std::vector<std::shared_ptr<Object>> objects;
        std::vector<std::shared_ptr<Light>> lights;
        Vec3 ambientLight;
    };

} // Raytracer
