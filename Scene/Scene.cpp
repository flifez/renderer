//
// Created by flif3 on 8/1/2023.
//

#include "Scene.h"

namespace Raytracer {
    void Scene::addObject(std::shared_ptr<Object> object) {
        objects.push_back(object);
    }

    void Scene::addLight(std::shared_ptr<Light> light) {
        lights.push_back(light);
    }

    const std::vector<std::shared_ptr<Object>>& Scene::getObjects() const {
        return objects;
    }

    const std::vector<std::shared_ptr<Light>>& Scene::getLights() const {
        return lights;
    }

    BasicCamera Scene::getCamera() const {
        return camera;
    }

    void Scene::setAmbientLight(const Vec3& ambLight) {
        this->ambientLight = ambLight;
    }

    const Vec3& Scene::getAmbientLight() const {
        return ambientLight;
    }

    HitInfo Scene::findClosestIntersection(const Ray &ray) const {
        HitInfo closestHitInfo(INFINITY, Vec3(), Vec3(), nullptr, MAX_DEPTH);
        for (std::shared_ptr<Object> object : objects) {
            HitInfo hitInfo = object->intersect(ray);
            if (hitInfo.t < closestHitInfo.t) {
                closestHitInfo = hitInfo;
            }
        }
        return closestHitInfo;
    }
} // Raytracer