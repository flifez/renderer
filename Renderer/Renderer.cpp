#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
//
// Created by flif3 on 8/2/2023.
//

#include "Renderer.h"

namespace Raytracer {
    void Renderer::render() const {
        int width = w;
        int height = h;

        std::vector<unsigned char> pixels(width * height * 3);

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                float u = float(x) / (width - 1);
                float v = float(y) / (height - 1);
                Ray ray = scene.getCamera().generateRay(u, v);
                HitInfo hitInfo = scene.findClosestIntersection(ray, 0);

                if (hitInfo.material == nullptr) {
                    Vec3 color = scene.getAmbient();

                    pixels[(y * width + x) * 3 + 0] = static_cast<unsigned char>(color.x * 255.99);
                    pixels[(y * width + x) * 3 + 1] = static_cast<unsigned char>(color.y * 255.99);
                    pixels[(y * width + x) * 3 + 2] = static_cast<unsigned char>(color.z * 255.99);

                } else if (hitInfo.material != nullptr) {
                    Vec3 color = calculateColor(ray, hitInfo);


                    // convert color from float to byte
                    pixels[(y * width + x) * 3 + 0] = static_cast<unsigned char>(color.x * 255.99);
                    pixels[(y * width + x) * 3 + 1] = static_cast<unsigned char>(color.y * 255.99);
                    pixels[(y * width + x) * 3 + 2] = static_cast<unsigned char>(color.z * 255.99);
                }
            }
        }

        stbi_write_png("image.png", width, height, 3, pixels.data(), width * 3);
    }

    Vec3 Renderer::calculateColor(const Ray& ray, const HitInfo& hitInfo) const {
        Vec3 color(0, 0, 0);  // Initialize color as black

        for (const std::shared_ptr<Light>& light : scene.getLights()) {
            Vec3 lightDirection = light->getDirection(hitInfo.point);
            Vec3 viewDirection = scene.getCamera().getDirection(hitInfo.point);
            Vec3 lightIntensity = light->getIntensity(hitInfo.point);
            Vec3 lightColor = light->getColor();
            color = color + hitInfo.material->shade(lightDirection,
                                                    viewDirection,
                                                    hitInfo.normal,
                                                    lightColor,
                                                    lightIntensity,
                                                    scene.getAmbient());
        }

        // add ambient light

        const_cast<HitInfo&>(hitInfo).depth++;

        // recursive raytracing: if we have not reached the maximum recursion depth (MAX_DEPTH), and the material is reflective or refractive, then we calculate the color of the reflected or refracted ray
        if (hitInfo.depth < MAX_DEPTH && (hitInfo.material->isReflective() || hitInfo.material->isRefractive())) {
            Ray reflectedRay = ray.reflect(hitInfo.point, hitInfo.normal);
            Ray refractedRay = ray.refract(hitInfo.point, hitInfo.normal, hitInfo.material->getRefractiveIndex());

            HitInfo reflectedHitInfo = scene.findClosestIntersection(reflectedRay, hitInfo.depth);
            HitInfo refractedHitInfo = scene.findClosestIntersection(refractedRay, hitInfo.depth);

            if (hitInfo.material->isReflective() && reflectedHitInfo.material != nullptr && reflectedHitInfo.material != hitInfo.material){ // quick fix; TODO: use epsilon offsetting
                color = color + calculateColor(reflectedRay, reflectedHitInfo) * hitInfo.material->getReflectivity();
            }

            if (hitInfo.material->isRefractive() && refractedHitInfo.material != nullptr) {
                color = color + calculateColor(refractedRay, refractedHitInfo) * hitInfo.material->getTransparency();
            }
        }

        return color;
    }

} // Raytracer
#pragma clang diagnostic pop