//
// Created by flif3 on 8/1/2023.
//

#include "Scene.h"

namespace Raytracer {
    void Scene::addObject(const std::shared_ptr<Object>& object) {
        objects.push_back(object);
        bvh.insert(object->getBoundingBox());
    }

    void Scene::addLight(const std::shared_ptr<Light>& light) {
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

    void Scene::setAmbient(const Vec3& ambColor, float ambIntensity) {
        this->ambient = ambColor * ambIntensity;
    }

    const Vec3& Scene::getAmbient() const {
        return ambient;
    }

    HitInfo Scene::findClosestIntersection(const Ray &ray, int depth) const {
        HitInfo closestHitInfo(INFINITY, Vec3(), Vec3(), nullptr, MAX_DEPTH);
        if (bvh.intersect(ray))
        {
            for (std::shared_ptr<Object> object: objects) {
                HitInfo hitInfo = object->intersect(ray, depth);
                if (hitInfo.t < closestHitInfo.t) {
                    closestHitInfo = hitInfo;
                }
            }
        }
        return closestHitInfo;
    }
} // Raytracer